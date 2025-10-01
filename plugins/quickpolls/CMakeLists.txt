include(BuildVeyonPlugin)

build_veyon_plugin(quickpolls
	QuickPollsFeaturePlugin.cpp
	QuickPollsDialog.cpp
	QuickPollsDialog.ui
	PollWidget.cpp
	PollWidget.ui
	PollResultsDialog.cpp
	PollResultsDialog.ui
	QuickPollsFeaturePlugin.h
	QuickPollsDialog.h
	PollWidget.h
	PollResultsDialog.h
	quickpolls.qrc
	)