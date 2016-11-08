#include "seguircor.hpp"
#include "basestate.hpp"
#include "robotino.hpp"
#include <cmath>

#define KpX 0.5
#define KiX 0.5*0

#define KpY 2.5
#define KiY 0.2*0

#define limiarAprox 30
#define limiarAprox2 8
#define limiarAprox3 6.1
#define limiarAproxLim 35

#define Kpir 10
#define Kpir2 20

#define dt 0.01


const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=50;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 20*20;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
//names that will appear at the top of each window
const string windowName = "Original Image";
//*****************************************************************************************************************
// SeguirCor
//*****************************************************************************************************************

SeguirCor  *SeguirCor::instance()
{
    static SeguirCor  SeguirCorInstance;
    return &SeguirCorInstance;
}

SeguirCor::SeguirCor() {}

SeguirCor::~SeguirCor() {}

string SCintToString(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void SCdrawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,SCintToString(theObjects.at(i).getXPos())+ " , " + SCintToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}

void SCmorphOps(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(17,17));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);
}

bool SCtrackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

    vector <Object> objects;
    Mat temp;
    threshold.copyTo(temp);
    //these two vectors needed for output of findContours
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;
    //find contours of filtered image using openCV findContours function
    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
    //use moments method to find our filtered object
    double refArea = 0;
    float distMin = 9999,dist;
    bool objectFound = false;

    if (hierarchy.size() > 0) {

        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

        //if the area is less than 20 px by 20px then it is probably just noise
        //if the area is the same as the 3/2 of the image size, probably just a bad filter
        //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREA){

                    Object object;

                    object.setXPos(moment.m10/area);
                    object.setYPos(moment.m01/area);
                    object.setType(theObject.getType());
                    object.setColor(theObject.getColor());
                    object.setHSVmin(theObject.getHSVmin());
                    object.setHSVmax(theObject.getHSVmax());

                    dist = sqrt(pow(theObject.getYPos()-object.getYPos(),2) + pow(theObject.getXPos()-object.getXPos(),2));

                    if (dist < distMin)
                    {

                    	distMin = dist;
                    	robotino->objetoAlvo = object;
                    	objects.clear();
                    	objects.push_back(object);
                    }

                    objectFound = true;


                }else objectFound = false;
            }
            //let user know you found an object
            if(objectFound ==true){
                //draw object location on screen
                SCdrawObject(objects,cameraFeed,temp,contours,hierarchy);

            }

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
    return objectFound;
}

void SeguirCor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado SeguirCor...\n";
}

void SeguirCor::execute(Robotino *robotino)
{

	//Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    static Mat threshold;
    static Mat thresholdr1;
    static Mat thresholdr2;
    static Mat HSV;
    static Mat src;
    static int etapasAprox = 0;
    float yAlvo = 195;
    float xAlvo = 166;

    bool alvo;

    // Obtendo a imagem do robô
    cameraFeed = robotino->getImage();
    src = cameraFeed;

    //convert frame from BGR to HSV colorspace
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);

    if(robotino->objetoAlvo.getType() == "red"){
        inRange(HSV,robotino->objetoAlvo.getHSVmin(),robotino->objetoAlvo.getHSVmax(),thresholdr1);
        inRange(HSV,Scalar(0,120,0),Scalar(8,255,255),thresholdr2);
        bitwise_or(thresholdr1,thresholdr2, threshold);
    }else{
        inRange(HSV,robotino->objetoAlvo.getHSVmin(),robotino->objetoAlvo.getHSVmax(),threshold);
    }

    SCmorphOps(threshold);
    alvo = SCtrackFilteredObject(robotino->objetoAlvo,threshold,HSV,cameraFeed, robotino);

    // Descomentar essa parte para mostrar o que está sendo seguido
    imshow(windowName,cameraFeed);
    cvMoveWindow(windowName.c_str(),500,300);
    waitKey(1);

    // Calculo dos erros em X (Horizontal) e Y (Vertical)
    float w,Vx,
            erroY   = -(robotino->objetoAlvo.getYPos() - yAlvo),
            erroX   = -(robotino->objetoAlvo.getXPos() - xAlvo);


    /* O metodo de aproximacao depende de onde o disco está

        etapaAprox 0 - Enquanto o sensor de distancia frontal não estiver vendo o disco
     		o robô usa a camera para seguir o disco
     	etapaAprox 1 - Depois que o valor lido pelo IR for menor que o limiar de aprox,
     		o robô usa o IR para se aproximar mais do disco
     	etapaAprox 2 - Devido a não linearidade do sensor, após ler 5 cm, o valor lido
     		pelo IR aumenta a medida que o objeto se aproxima, ele segue assim, até o
     		objeto estar a 9 cm, o que na verdade é encostado na garra.
     	etapaAprox 3 - O disco está completamente na garra, retorna-se entao ao estado
     		anterior
     	Nota - Se durante a etapa 2, o valor limite for maior que o limiar de aproximacao
     		limite, retorna-se a etapa de aproximacao 0
    */
    if(robotino->irDistance(Robotino::IR_FRONTAL) < limiarAprox && (etapasAprox == 0 || etapasAprox == 1)){
    	etapasAprox = 1;
    }if(robotino->irDistance(Robotino::IR_FRONTAL) < limiarAprox2 && (etapasAprox == 1 || etapasAprox == 2)){
    	etapasAprox = 3; // Mudou aqui, tirou a etapa 2
    }if(robotino->irDistance(Robotino::IR_FRONTAL) > limiarAprox3 &&  etapasAprox == 2){
    	etapasAprox = 3;
    }if(robotino->irDistance(Robotino::IR_FRONTAL) > limiarAproxLim){ //&& etapasAprox == 2){
    	etapasAprox = 0;
    }

    // Calculo das velocidades de acordo com cada etapa
    if(etapasAprox == 0){
	w  = KpX*erroX;
    	Vx   = KpY*erroY;
    }else if(etapasAprox == 1){
    	w = 0;
    	Vx = Kpir*robotino->irDistance(Robotino::IR_FRONTAL);
    }else if(etapasAprox == 2){
    	w = 0;
    	Vx = -Kpir2*(robotino->irDistance(Robotino::IR_FRONTAL)-limiarAprox3);
    }




   	std::cout << "Etapa: " << etapasAprox << "\n";
    std::cout << "W: " << w << "\n";

	std::cout << "Distancia: " << robotino->irDistance(Robotino::IR_FRONTAL) << "\n";

    robotino->setVelocity(Vx,0,w);
    if (etapasAprox == 3){
    	//robotino->setCarregando(true);
    	robotino->change_state(robotino->previous_state());
    	etapasAprox = 0;
    }
}

void SeguirCor::exit(Robotino *robotino) {
	std::cout << "O disco está na garra\n";
	robotino->setVelocity(0,0,0);
}
