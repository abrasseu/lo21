QT += core gui widgets

SOURCES += \
		main.cpp \
	autocell/Rule.cpp \
	autocell/Simulator.cpp \
	autocell/Simulator1D.cpp \
	autocell/Simulator2D.cpp \
	autocell/SimulatorLifeGame.cpp \
	autocell/State.cpp \
	autocell/SimulatorManager.cpp \
#	interface/interf.cpp \
#	interface/inter_1d.cpp \
#	interface/inter_2d.cpp \
	interface/HomeView.cpp \
	interface/SimulatorInterface.cpp \
	interface/Interface1D.cpp \
	interface/Interface2D.cpp \
	interface/TransitionInterface.cpp

HEADERS += \
	autocell/Rule.h \
	autocell/Simulator.h \
	autocell/Simulator1D.h \
	autocell/Simulator2D.h \
	autocell/SimulatorLifeGame.h \
	autocell/State.h \
	autocell/SimulatorManager.h \
#	interface/inclu_fich.h \
#	interface/interf.h \
#	interface/inter_1d.h \
#	interface/inter_2d.h \
	interface/HomeView.h \
	interface/SimulatorInterface.h \
	interface/Interface1D.h \
	interface/Interface2D.h \
	interface/TransitionInterface.h
