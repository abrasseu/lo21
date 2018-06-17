QT += core gui widgets

SOURCES += \
	main.cpp \
	autocell/Rule.cpp \
	autocell/SimulatorException.cpp \
	autocell/Simulator.cpp \
	autocell/Simulator1D.cpp \
	autocell/Simulator2D.cpp \
	autocell/State.cpp \
	autocell/SimulatorManager.cpp \
	interface/HomeView.cpp \
	interface/SimulatorInterface.cpp \
	interface/Interface1D.cpp \
	interface/Interface2D.cpp \
	interface/TransitionInterface.cpp \
	interface/StateInterface.cpp

HEADERS += \
	autocell/Rule.h \
	autocell/SimulatorException.h \
	autocell/Simulator.h \
	autocell/Simulator1D.h \
	autocell/Simulator2D.h \
	autocell/State.h \
	autocell/SimulatorManager.h \
	interface/HomeView.h \
	interface/SimulatorInterface.h \
	interface/Interface1D.h \
	interface/Interface2D.h \
	interface/TransitionInterface.h \
	interface/StateInterface.h
