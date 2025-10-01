include(BuildVeyonPlugin)

build_veyon_plugin(polls
	NAME Polls
	SOURCES
	PollsFeaturePlugin.cpp
	PollDialog.cpp
	PollQuestionDialog.cpp
	PollResultsDialog.cpp
	PollsFeaturePlugin.h
	PollDialog.h
	PollQuestionDialog.h
	PollResultsDialog.h
	PollDialog.ui
	PollQuestionDialog.ui
	PollResultsDialog.ui
	polls.qrc
	)