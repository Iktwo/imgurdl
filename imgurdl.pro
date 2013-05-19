QT += declarative network xml

SOURCES += \
    src/main.cpp \
    src/hashcalculator.cpp \
    src/downloader.cpp \
    src/downloadercomponent.cpp \
    src/imageur.cpp

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    qml/main.qml \
    qml/Checkbox.qml

HEADERS += \
    src/hashcalculator.h \
    src/downloader.h \
    src/downloadercomponent.h \
    src/imageur.h
