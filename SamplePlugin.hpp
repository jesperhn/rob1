#ifndef SAMPLEPLUGIN_HPP
#define SAMPLEPLUGIN_HPP

#include "ui_SamplePlugin.h"

#include <rws/RobWorkStudioPlugin.hpp>

#include <rw/kinematics/State.hpp>

class SamplePlugin: public rws::RobWorkStudioPlugin, private Ui::SamplePlugin
{
Q_OBJECT
Q_INTERFACES( rws::RobWorkStudioPlugin )
public:
	SamplePlugin();
	virtual ~SamplePlugin();

	virtual void open(rw::models::WorkCell* workcell);

	virtual void GetFWTMatrix(rw::math::Q toPoint);

	virtual void close();

	virtual void initialize();

private slots:
	void btnPressed();

	void stateChangedListener(const rw::kinematics::State& state);
};

#endif /*RINGONHOOKPLUGIN_HPP_*/
