include(BuildVeyonPlugin)

build_veyon_plugin(classroomtimer
	ClassroomTimerFeaturePlugin.cpp
	ClassroomTimerDialog.cpp
	ClassroomTimerDialog.ui
	TimerWidget.cpp
	TimerWidget.ui
	ClassroomTimerFeaturePlugin.h
	ClassroomTimerDialog.h
	TimerWidget.h
	classroomtimer.qrc
	)