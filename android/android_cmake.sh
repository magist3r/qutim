CODEDIR=/home/magist3r/code

cmake $CODEDIR/qutim \
-DANDROID_NDK=$CODEDIR/necessitas/android-ndk \
-DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.6 \
-DCMAKE_TOOLCHAIN_FILE=$CODEDIR/android-cmake/toolchain/android.toolchain.cmake \
-DCMAKE_VERBOSE_MAKEFILE=1 \
-DANDROID_NATIVE_API_LEVEL=android-14 \
-DANDROID_FORCE_ARM_BUILD=0 \
-DCMAKE_BUILD_TYPE=Debug \
-DCMAKE_INSTALL_PREFIX=/usr \
-DANDROID_USE_STLPORT=0 \
-DQT_QMAKE_EXECUTABLE=$CODEDIR/qt-android/bin/qmake \
-DQT_LIBRARY_DIR=$CODEDIR/qt-android/lib \
-DQT_INCLUDE_DIR=$CODEDIR/qt-android/include \
-DQT_MOC_EXECUTABLE=$CODEDIR/qt-android/bin/moc \
-DQT_UIC_EXECUTABLE=$CODEDIR/qt-android/bin/uic \
-DQT_RCC_EXECUTABLE=$CODEDIR/qt-android/bin/rcc \
-DQT_QTGUI_LIBRARY=$CODEDIR/qt-android/lib/libQtGui.so \
-DQT_QTGUI_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtGui.so \
-DQT_QTGUI_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtGui.so \
-DQT_QTCORE_INCLUDE_DIR=$CODEDIR/qt-android/include/QtCore \
-DQT_QTGUI_INCLUDE_DIR=$CODEDIR/qt-android/include/QtGui \
-DQT_QTMULTIMEDIA_INCLUDE_DIR=$CODEDIR/qt-android/include/QtMultimedia \
-DQT_QTNETWORK_INCLUDE_DIR=$CODEDIR/qt-android/include/QtNetwork \
-DQT_QTSCRIPT_INCLUDE_DIR=$CODEDIR/qt-android/include/QtScript \
-DQT_QTSQL_INCLUDE_DIR=$CODEDIR/qt-android/include/QtSql \
-DQT_QTSVG_INCLUDE_DIR=$CODEDIR/qt-android/include/QtSvg \
-DQT_QTTEST_INCLUDE_DIR=$CODEDIR/qt-android/include/QtTest \
-DQT_QTWEBKIT_INCLUDE_DIR=$CODEDIR/qt-android/include/QtWebKit \
-DQT_QTXML_INCLUDE_DIR=$CODEDIR/qt-android/include/QtXml \
-DQT_QTXMLPATTERNS_INCLUDE_DIR=$CODEDIR/qt-android/include/QtXmlPatterns \
-DQT_QTSCRIPTTOOLS_INCLUDE_DIR=$CODEDIR/qt-android/include/QtScriptTools \
-DQT_QTDECLARATIVE_INCLUDE_DIR=$CODEDIR/qt-android/include/QtDeclarative \
-DQT_QTCORE_LIBRARY=$CODEDIR/qt-android/lib/libQtCore.so \
-DQT_QTCORE_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtCore.so \
-DQT_QTCORE_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtCore.so \
-DQT_QTMULTIMEDIA_LIBRARY=$CODEDIR/qt-android/lib/libQtMultimedia.so \
-DQT_QTMULTIMEDIA_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtMultimedia.so \
-DQT_QTMULTIMEDIA_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtMultimedia.so \
-DQT_QTNETWORK_LIBRARY=$CODEDIR/qt-android/lib/libQtNetwork.so \
-DQT_QTNETWORK_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtNetwork.so \
-DQT_QTNETWORK_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtNetwork.so \
-DQT_QTSCRIPT_LIBRARY=$CODEDIR/qt-android/lib/libQtScript.so \
-DQT_QTSCRIPT_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtScript.so \
-DQT_QTSCRIPT_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtScript.so \
-DQT_QTXML_LIBRARY=$CODEDIR/qt-android/lib/libQtXml.so \
-DQT_QTXML_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtXml.so \
-DQT_QTXML_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtXml.so \
-DQT_QTXMLPATTERNS_LIBRARY=$CODEDIR/qt-android/lib/libQtXmlPatterns.so \
-DQT_QTXMLPATTERNS_LIBRARY_DEBUG=$CODEDIR/qt-android/lib/libQtXmlPatterns.so \
-DQT_QTXMLPATTERNS_LIBRARY_RELEASE=$CODEDIR/qt-android/lib/libQtXmlPatterns.so \
-DDECLARATIVE_UI=1 \
-DDBUSAPI=off \
-DADDCONTACTDLG=off \
-DADIUMCHAT=off \
-DAESCRYPTO=off \
-DANTIBOSS=off \
-DASPELLER=off \
-DASTRAL=off \
-DAWN=off \
-DCHATSPELLCHECKER=off \
-DCONNECTIONMANAGER=off \
-DCONTACTINFO=off \
-DDATAFORMSBACKEND=off \
-DEMOTICONSSETTINGS=off \
-DFILETRANSFER=off \
-DFILETRANSFERSETTINGS=off \
-DFLOATIES=off \
-DHISTMAN=off \
-DHUMANITY=off \
-DIDLEDETECTOR=off \
-DIDLESTATUSCHANGER=off \
-DINDICATOR=off \
-DJOINCHATDIALOG=off \
-DJOINGROUPCHATDLG=off \
-DKDEINTEGRATION=off \
-DKINETICPOPUPS=off \
-DKINETICSCROLLER=off \
-DLOGGER=off \
-DMACINTEGRATION=off \
-DMETACONTACTS=off \
-DMIGRATION02X03=off \
-DMOBILEABOUT=0 \
-DMOBILECONTACTINFO=1 \
-DMOBILESETTINGSDIALOG=1 \
-DMOBILENOTIFICATIONSSETTINGS=1 \
-DNOTIFICATIONSSETTINGS=0 \
-DNOWPLAYING=off \
-DOLDCONTACTDELEGATE=off \
-DPLISTCONFIG=off \
-DPLUGMAN=off \
-DQMLCHAT=off \
-DQRCICONS=0 \
-DQSOUNDBACKEND=off \
-DQUETZAL=off \
-DSCRIPTAPI=off \
-DSDLSOUND=off \
-DSEARCHDIALOG=off \
-DSERVICECHOOSER=off \
-DSIMPLEABOUT=off \
-DSIMPLECONTACTLIST=on \
-DSOFTKEYSACTIONBOX=off \
-DSYMBIANINTEGRATION=off \
-DTABBEDCHATFORM=off \
-DTRAYICON=off \
-DUNITYLAUNCHER=off \
-DWEATHER=off \
-DWININTEGRATION=off \
-DWITH_DOXYGEN=off \
-DXSETTINGSDIALOG=off \
-DAWN=off \
-DASPELLER=off \
-DYANDEXNAROD=off \
-DWEATHER=off \
-DHISTMAN=off \
-DDBUSNOTIFICATIONS=off \
-DLOGGER=off \
-DHUNSPELLER=off \
-DCONNECTIONMANAGER=off \
-DAESCRYPTO=off \
-DINDICATOR=off \
-DSDLSOUND=off \
-DNOWPLAYING=off \
-DDBUSAPI=off \
-DPHONONSOUND=off \
-DCLCONF=off \
-DMASSMESSAGING=off \
-DMEEGOINTEGRATION=off \
-DANDROIDINTEGRATION=0 \
\
-DQUETZAL=off \
-DASTRAL=off \
-DVKONTAKTE=off \
-DIRC=off \
\
-DQTICONS=off \
-DMIGRATION02X03=off \
-DSOUNDTHEMESELECTOR=off \
-DOLDSOUNDTHEME=off \
-DQSOUNDBACKEND=off \
-DJABBER=off \
-DMULTIMEDIABACKEND=off \
-DEMOEDIT=off \
-DANTISPAM=off \
-DOSCAR_USE_3RDPARTY_HMAC=1 \
-DDOCKTILE=0 \
-DOFFTHERECORD=0 \
-DQT_LCONVERT_EXECUTABLE="/usr/bin/lconvert" \

#-DQUTIM_BINARY_DIR=/home/kkszysiu/code/android/fun/qutim_mw/ \
#-DQUTIM_PATH=/home/kkszysiu/Dokumenty/android/lib/libqutim.so \
#-DQUTIM_LIBRARY=/home/kkszysiu/Dokumenty/android/lib/

#-DQUTIM_BASE_LIBRARY_TYPE=STATIC \
#-DCMAKE_VERBOSE_MAKEFILE=TRUE \
#-DANDROID=TRUE \
#-D__ANDROID__=TRUE \
#-DQUTIM_MOBILE_UI=TRUE \
#-VERBOSE=0 \
#-DQTDIR=$CODEDIR/qt-android/ \
#\
#-DQCA2_LIBRARIES=/home/kkszysiu/Pobrane/qca-2.0.3/lib/libqca.so \
#-DQCA2_INCLUDE_DIR=/home/kkszysiu/Pobrane/qca-2.0.3/include/QtCrypto/ \
#\
#-DZLIB_INCLUDE_DIR=/usr/local/android-ndk-r4-crystax/build/platforms/android-5/arch-arm/usr/include/ \
#-DZLIB_LIBRARY=/usr/local/android-ndk-r4-crystax/build/platforms/android-5/arch-arm/usr/lib/libz.so \
#\
#-DWIN-INTEGRATION=off \
#-DKDE-INTEGRATION=off \
#-DANDROID-INTEGRATION=off \
