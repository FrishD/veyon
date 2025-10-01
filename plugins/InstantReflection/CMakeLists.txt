include(BuildVeyonPlugin)

build_veyon_plugin(instantreflection
	NAME InstantReflection
	SOURCES
	InstantReflectionFeaturePlugin.cpp
	ReflectionStatusDialog.cpp
	InstantReflectionFeaturePlugin.h
	ReflectionStatusDialog.h
	ReflectionStatusDialog.ui
	instantreflection.qrc
	)