#include "percorrerquadradoprocurandodiscos.hpp"
#include "robotino.hpp"
#include "identificarcor.hpp"

#include <cmath>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#define PI 3.14159265
#define Kpx 2
#define KpW 4
#define yRef 220 //yRef 180
#define N 6
#define limiarParada 12
//default capture width and height
const int FRAME_WIDTHPQCD = 640;
const int FRAME_HEIGHTPQCD = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTSPQCD=50;
//minimum and maximum object area
const int MIN_OBJECT_AREAPQCD = 20*20;
const int MAX_OBJECT_AREAPQCD = FRAME_HEIGHTPQCD*FRAME_WIDTHPQCD/1.5;
//names that will appear at the top of each window
const string windowNamePQCD = "Original Image";
//*****************************************************************************************************************
// PercorrerQuadradoProcurandoDiscos
//*****************************************************************************************************************

PercorrerQuadradoProcurandoDiscos  *PercorrerQuadradoProcurandoDiscos::instance()
{
    static PercorrerQuadradoProcurandoDiscos  PercorrerQuadradoProcurandoDiscosStateInstance;
    return &PercorrerQuadradoProcurandoDiscosStateInstance;
}

PercorrerQuadradoProcurandoDiscos::PercorrerQuadradoProcurandoDiscos() {}

PercorrerQuadradoProcurandoDiscos::~PercorrerQuadradoProcurandoDiscos() {}

void PercorrerQuadradoProcurandoDiscos::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado PercorrerQuadradoProcurandoDiscos...\n";
}

string intToStringPQCD(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObjectPQCD(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,intToStringPQCD(theObjects.at(i).getXPos())+ " , " + intToStringPQCD(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}

void morphOpsPQCD(Mat &thresh){

    //create structuring element that will be used to "dilate" and "erode" image.
    //the element chosen here is a 3px by 3px rectangle
    Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
    //dilate with larger element so make sure object is nicely visible
    Mat dilateElement = getStructuringElement( MORPH_RECT,Size(17,17));

    erode(thresh,thresh,erodeElement);
    erode(thresh,thresh,erodeElement);

    dilate(thresh,thresh,dilateElement);
    dilate(thresh,thresh,dilateElement);

   // imshow("morph2",thresh);
   // waitKey(1);
}

bool trackFilteredObjectPQCD(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

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
    bool objectFound = false;

    if(theObject.getType() == "red"){
        robotino->objetosVermelhos.clear() ;
    }else if(theObject.getType() == "blue"){
        robotino->objetosAzuis.clear() ;
    }else if(theObject.getType() == "yellow"){
        robotino->objetosAmarelos.clear() ;
    }

    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();
        //if number of objects greater than MAX_NUM_OBJECTSPQCD we have a noisy filter
        if(numObjects<MAX_NUM_OBJECTSPQCD){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

        //if the area is less than 20 px by 20px then it is probably just noise
        //if the area is the same as the 3/2 of the image size, probably just a bad filter
        //we only want the object with the largest area so we safe a reference area each
                //iteration and compare it to the area in the next iteration.
                if(area>MIN_OBJECT_AREAPQCD){

                    Object object;

                    object.setXPos(moment.m10/area);
                    object.setYPos(moment.m01/area);
                    object.setType(theObject.getType());
                    object.setColor(theObject.getColor());
                    object.setHSVmin(theObject.getHSVmin());
                    object.setHSVmax(theObject.getHSVmax());

                    objects.push_back(object);

                    objectFound = true;

                    if(theObject.getType() == "red"){
                        robotino->objetosVermelhos.push_back(object);
                    }else if(theObject.getType() == "blue"){
                        robotino->objetosAzuis.push_back(object);
                    }else if(theObject.getType() == "yellow"){
                        robotino->objetosAmarelos.push_back(object);
                    }

                }else objectFound = false;
            }
            //let user know you found an object
            if(objectFound ==true){
                //draw object location on screen
                drawObjectPQCD(objects,cameraFeed,temp,contours,hierarchy);

            }

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
    return objectFound;
}


void PercorrerQuadradoProcurandoDiscos::execute(Robotino *robotino)
{
    Mat img, cdst;
    int min_Hough = 70, dist_Hough = 50;
    int min_canny =150 , max_canny = 3*min_canny;
    float angLinhas = 0, angulo = 0;
    float xMedio = 0;
    float  mediaX = 0;
    float yMaior = -1;
    float erros;
    float Vx, w, Vy = robotino->getVelocidadeBusca();
    int cor = -1;
    static bool entrei = false;
    vector<Vec4i> lines;
    Vec4i l, l2;
    static float valoresX[N];
    static int  n = 0;
    static State<Robotino> * voltar;

    img = robotino->getImage();

    cvtColor( img, cdst, CV_BGR2GRAY );

    Canny( cdst, cdst, (double)min_canny, (double)max_canny, 3 );
    convertScaleAbs(cdst, cdst);

    //cv::imshow("Canny",cdst);
    //cv::waitKey(1);

    threshold(cdst, cdst, (double)5, (double)255, CV_THRESH_BINARY);

    HoughLinesP(cdst, lines, 1, CV_PI/180, min_Hough, min_Hough, dist_Hough );

    cvtColor( cdst, cdst, CV_GRAY2BGR );

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      angulo = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      if(l[3] > yMaior  && abs(angulo) < 60){
        yMaior = l[3];
        angLinhas = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      }
      if(l[1] > yMaior && abs(angulo) < 60){
        yMaior = l[1];
        angLinhas = atan2((l[3] - l[1]),(l[2]-l[0]))*180/PI;
      }
    }

    std::cout << "Angulo da linha mais perto "<< angLinhas <<"\n";
    std::cout << "Y maior "<< yMaior <<"\n";
    std::cout << "Media dos Xs " << mediaX << "\n";

    for( size_t i = 0; i < lines.size(); i++ ){
      Vec4i l = lines[i];
      line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 1, CV_AA);
    }

    float erro_x = yRef - yMaior,

    erro_theta = -angLinhas;

    Vx = Kpx*erro_x;
    w = KpW*erro_theta;

    erros = abs(erro_x)+abs(erro_theta);

    std::cout<<"Soma dos erros: " << erros <<std::endl;

    if (!entrei){
        voltar = robotino->previous_state();
        robotino->objetosAmarelos.clear();
        robotino->objetosAzuis.clear();
        robotino->objetosVermelhos.clear();
        entrei = true;
    }


//Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    static Mat threshold;
    static Mat thresholdr1;
    static Mat thresholdr2;
    static Mat HSV;
    static Mat src;

    cameraFeed = img;
    src = cameraFeed;

    //convert frame from BGR to HSV colorspace
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);


    //create some temp fruit objects so that
    //we can use their member functions/information
    Object blue("blue"), yellow("yellow"), red("red"), black("black");
    bool azul, amarelo, vermelho, preto;

    //first find blue objects
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,blue.getHSVmin(),blue.getHSVmax(),threshold);
    morphOpsPQCD(threshold);
    azul = trackFilteredObjectPQCD(blue,threshold,HSV,cameraFeed, robotino);
    //then yellows
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,yellow.getHSVmin(),yellow.getHSVmax(),threshold);
    morphOpsPQCD(threshold);
    amarelo = trackFilteredObjectPQCD(yellow,threshold,HSV,cameraFeed, robotino);
    //then reds
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,red.getHSVmin(),red.getHSVmax(),thresholdr1);
    inRange(HSV,Scalar(0,120,0),Scalar(8,255,255),thresholdr2);
    bitwise_or(thresholdr1,thresholdr2, threshold);
    morphOpsPQCD(threshold);
    vermelho = trackFilteredObjectPQCD(red,threshold,HSV,cameraFeed, robotino);

    //then blacks
    // cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    // inRange(HSV,black.getHSVmin(),black.getHSVmax(),threshold);
    // morphOpsPQCDBlack(threshold);
    // preto = trackFilteredObjectPQCD(black,threshold,HSV,cameraFeed, robotino);


    if (azul)
        cout << "Azul: " << robotino->objetosAzuis.size() << endl;
     if (amarelo)
        cout << "Amarelo: " << robotino->objetosAmarelos.size() << endl;
     if (vermelho)
        cout << "Vermelho: " << robotino->objetosVermelhos.size() << endl;
    //if (preto)
       // cout << "Preto: " << robotino->objetosPretos.size() << endl;

    imshow(windowNamePQCD,cameraFeed);
    cvMoveWindow(windowNamePQCD.c_str(),500,300);
    //imshow(windowNamePQCD1,HSV);

    //delay 30ms so that screen can refresh.
    //image will not appear without this waitKey() command
    waitKey(1);



    if (robotino->objetosAmarelos.size() > 0 || robotino->objetosVermelhos.size() > 0 || robotino->objetosAzuis.size() > 0 ){

        // if(robotino->objetosAmarelos.size() > 0){
        //     cor = Robotino::AMARELO;
        // }else if(robotino->objetosVermelhos.size() > 0){
        //     cor = Robotino::VERMELHO;
        // }else if(robotino->objetosAzuis.size() > 0){
        //      cor = Robotino::AZUL;
        // }

        //if (robotino->corFaltando(cor)){
        robotino->definirObjetoAlvo(Robotino::TODAS);
        //robotino->removerCorFaltando(cor);
        robotino->setVelocity(0,0,0);
        entrei = false;
        robotino->change_state(voltar);
        //}

    }else{
        robotino->setVelocity(Vx,Vy,w);
    }

    cv::imshow("Linha", cdst);
    cv::waitKey(1);

}

void PercorrerQuadradoProcurandoDiscos::exit(Robotino *robotino) {}
