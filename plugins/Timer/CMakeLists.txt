include(BuildVeyonPlugin)

build_veyon_plugin(timer
	NAME Timer
	SOURCES
	TimerFeaturePlugin.cpp
	TimerDialog.cpp
	TimerDialog.ui
	TimerFeaturePlugin.h
	TimerDialog.h
	timer.qrc
	)