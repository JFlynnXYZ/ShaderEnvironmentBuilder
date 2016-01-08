# This specifies the exe name
TARGET=CEB
# where to put the .o files
OBJECTS_DIR=obj
# core Qt Libs to use add more here if needed.
QT+=gui opengl core

# as I want to support 4.8 and 5 this will set a flag for some of the mac stuff
# mainly in the types.h file for the setMacVisual which is native in Qt5
isEqual(QT_MAJOR_VERSION, 5) {
	cache()
	DEFINES +=QT5BUILD
}

# where to put moc auto generated files
MOC_DIR=moc
# on a mac we don't create a .app bundle file ( for ease of multiplatform use)
CONFIG-=app_bundle
# Auto include all .cpp files in the project src directory (can specifiy individually if required)
SOURCES+= $$PWD/src/*.cpp
# same for the .h files
HEADERS+= $$PWD/include/*.h
FORMS+= $$PWD/ui/MainWindow.ui
# and add the include dir into the search path for Qt and make
INCLUDEPATH +=./include
# where our exe is going to live (root of project)
DESTDIR=./
# add the glsl shader files
OTHER_FILES+= $$PWD/shaders/*.glsl /
              README.md
# were are going to default to a console app
CONFIG += console
NGLPATH=$$(NGLDIR)
isEmpty(NGLPATH){ # note brace must be here
	message("including $HOME/NGL")
	include($(HOME)/NGL/UseNGL.pri)
}
else{ # note brace must be here
	message("Using custom NGL location")
	include($(NGLDIR)/UseNGL.pri)
}


# include QSci headers and lib
LIBS += $$PWD/lib/libqscintilla2.a

# include Flex libs
LIBS += $$PWD/lib/libfl.a

# Auto include all .lex and .cc files for Flex
OTHER_FILES+= $$PWD/src/*.lex
SOURCES+= $$PWD/src/*.cc
