#include "identificarcor.hpp"
#include "robotino.hpp"
#include "object.hpp"
#include "seguircor.hpp"

//default capture width and height
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
// IdentificarCor
//*****************************************************************************************************************

IdentificarCor  *IdentificarCor::instance()
{
    static IdentificarCor  IdentificarCorStateInstance;
    return &IdentificarCorStateInstance;
}

IdentificarCor::IdentificarCor() {}

IdentificarCor::~IdentificarCor() {}

void IdentificarCor::enter(Robotino *robotino)
{
    std::cout << "Entrando no estado IdentificarCor...\n";
}

string intToString(int number){

    std::stringstream ss;
    ss << number;
    return ss.str();
}

void drawObject(vector<Object> theObjects,Mat &frame, Mat &temp, vector< vector<Point> > contours, vector<Vec4i> hierarchy){

    for(int i =0; i<theObjects.size(); i++){
    cv::drawContours(frame,contours,i,theObjects.at(i).getColor(),3,8,hierarchy);
    cv::circle(frame,cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()),5,theObjects.at(i).getColor());
    cv::putText(frame,intToString(theObjects.at(i).getXPos())+ " , " + intToString(theObjects.at(i).getYPos()),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()+20),1,1,theObjects.at(i).getColor());
    cv::putText(frame,theObjects.at(i).getType(),cv::Point(theObjects.at(i).getXPos(),theObjects.at(i).getYPos()-20),1,2,theObjects.at(i).getColor());
    }
}

void morphOps(Mat &thresh){

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


bool trackFilteredObject(Object theObject,Mat threshold,Mat HSV, Mat &cameraFeed, Robotino* robotino){

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
                drawObject(objects,cameraFeed,temp,contours,hierarchy);

            }

        }else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
    }
    return objectFound;
}


void IdentificarCor::execute(Robotino *robotino)
{
    //Matrix to store each frame of the webcam feed
    static Mat cameraFeed;
    static Mat threshold;
    static Mat thresholdr1;
    static Mat thresholdr2;
    static Mat HSV;
    static Mat src;

    //cv::waitKey();

    cameraFeed = robotino->getImage();
    src = cameraFeed;

    //convert frame from BGR to HSV colorspace
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);


    //create some temp fruit objects so that
    //we can use their member functions/information
    Object blue("blue"), yellow("yellow"), red("red");
    bool azul, amarelo, vermelho;

    //first find blue objects
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,blue.getHSVmin(),blue.getHSVmax(),threshold);
    morphOps(threshold);
    azul = trackFilteredObject(blue,threshold,HSV,cameraFeed, robotino);
    //then yellows
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,yellow.getHSVmin(),yellow.getHSVmax(),threshold);
    morphOps(threshold);
    amarelo = trackFilteredObject(yellow,threshold,HSV,cameraFeed, robotino);
    //then reds
    cvtColor(cameraFeed,HSV,COLOR_BGR2HSV);
    inRange(HSV,red.getHSVmin(),red.getHSVmax(),thresholdr1);
    inRange(HSV,Scalar(0,120,0),Scalar(8,255,255),thresholdr2);
    bitwise_or(thresholdr1,thresholdr2, threshold);
    morphOps(threshold);
    vermelho = trackFilteredObject(red,threshold,HSV,cameraFeed, robotino);

    if (azul)
        cout << "Azul: " << robotino->objetosAzuis.size() << endl;
     if (amarelo)
        cout << "Amarelo: " << robotino->objetosAmarelos.size() << endl;
     if (vermelho)
        cout << "Vermelho: " << robotino->objetosVermelhos.size() << endl;

    //imshow(windowName,cameraFeed);
    //imshow(windowName1,HSV);

    //delay 30ms so that screen can refresh.
    //image will not appear without this waitKey() command
    //waitKey(1);

    //robotino->definirObjetoAlvo(Robotino::AZUL);

    //robotino->change_state(SeguirCor::instance());
    robotino->change_state(robotino->previous_state());
}

void IdentificarCor::exit(Robotino *robotino) {}
