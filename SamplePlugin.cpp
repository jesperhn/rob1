#include "SamplePlugin.hpp"

#include <rws/RobWorkStudio.hpp>
#include <rw/rw.hpp>
#include <QPushButton>

USE_ROBWORK_NAMESPACE
using namespace robwork;

using namespace rw::kinematics;
using namespace rw::models;
using namespace rws;
//using namespace rw::loaders;

WorkCell::Ptr wc;

SamplePlugin::SamplePlugin():
    RobWorkStudioPlugin("SamplePluginUI", QIcon(":/pa_icon.png"))
{
	setupUi(this);

	// now connect stuff from the ui component
	connect(_btn0    ,SIGNAL(pressed()), this, SLOT(btnPressed()) );
	connect(_btn1    ,SIGNAL(pressed()), this, SLOT(btnPressed()) );
	connect(_btn2    ,SIGNAL(pressed()), this, SLOT(btnPressed()) );
	connect(_spinBox  ,SIGNAL(valueChanged(int)), this, SLOT(btnPressed()) );

}

SamplePlugin::~SamplePlugin()
{
}

void SamplePlugin::initialize() {

	getRobWorkStudio()->stateChangedEvent().add(boost::bind(&SamplePlugin::stateChangedListener, this, _1), this);
}


void SamplePlugin::open(WorkCell* workcell)
{

	wc = rw::loaders::WorkCellFactory::load("/home/jesperhn/eclipse_workspace/rob/project1/rob_scenes/Kr16WorkCell/Scene.wc.xml");

//	std::string deviceName = "KukaKr16";
//	Device::Ptr device;
//
//	State state = wc->getDefaultState();
//	device = wc->findDevice(deviceName);
//	Q q(6, 1,1,1,1,1,1);
//
//	device->setQ(q, state);

	//getRobWorkStudio()->setState(state);
//	//const std::string frameName = "UR";
//	 Log::infoLog() << "Name of workcell: " << wc->getName() << std::endl;
//	 Log::infoLog() << "Device: " << wc->getDevices() << std::endl;

	 //	 // get the default state
//	 State state = wc->getDefaultState();
//	 Log::infoLog() << "Default State: " << state;
//	 Frame* worldFrame = wc->getWorldFrame();
	 // find a frame by name, remember NULL is a valid return
//	 Frame* frame = wc->findFrame("Robot");
	 // find a frame by name, but with a specific frame type
//	 FixedFrame* fframe = wc->findFrame<FixedFrame>("Robot");
	 //MovableFrame* mframe = wc->findFrame<MovableFrame>("MovableFrameName");
//	 // find a device by name
//	// Device* wc->findDevice("SerialDeviceName");
//	 //SerialDevice* wc->findDevice<SerialDevice>("SerialDeviceName");
}

void SamplePlugin::close() {
}

void SamplePlugin::GetFWTMatrix(Q toPoint)
{

	State state = getRobWorkStudio()->getState();
	Device::Ptr device = wc->getDevices().front();
	device ->setQ(toPoint,state);
	Transform3D<double> transformation = device->baseTend(state);
	log().info()
			<< device->getBase()->getName()
			<< transformation.P();

}

void SamplePlugin::btnPressed() {
	QObject *obj = sender();
	if(obj==_btn0){
		Q P(6,20,20,20,20,20,20);
		SamplePlugin::GetFWTMatrix(P);
		log().info() << "Button 0\n";
	} else if(obj==_btn1){
		log().info() << "Button 1\n";
	}  else if(obj==_btn2){
		log().info() << "Task 2 - Base to bottle and bottle to TCP transformation\n";
		//get tool frame of the robot
		Frame* toolFrame = wc->findFrame("KukaKr16.Joint6");
		//get frame of the object/bottle to  be picked up
		Frame* bottleFrame = wc->findFrame("Bottle");
		State state = getRobWorkStudio()->getState();

		Device::Ptr device = wc->getDevices().front();
		Transform3D<double> tfBaseToBottle = device->baseTframe(bottleFrame, state);
		log().info()
				<< device->getBase()->getName()
				<< "at"
				<< tfBaseToBottle.P()
				<< "\n";

		log().info() << "Button 2\n";
	} else if(obj==_spinBox){
		log().info() << "spin value:" << _spinBox->value() << "\n";
	}
}

void SamplePlugin::stateChangedListener(const State& state) {
}

Q_EXPORT_PLUGIN(SamplePlugin);
