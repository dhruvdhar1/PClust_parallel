from PyQt4 import QtCore, QtGui
import sys,os
from output1 import showGraph1
from output2 import showGraph2
from saveGraph import saveGraph3
from upload_S3 import compress
try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        w = QtGui.QDesktopWidget().availableGeometry().width() * 0.33
        h = QtGui.QDesktopWidget().availableGeometry().height() * 0.33
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(500, 320)
        Dialog.setWindowFlags(QtCore.Qt.FramelessWindowHint)
        Dialog.move(w,h)
        self.label = QtGui.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(-10, -10, 520, 331))
        self.label.setText(_fromUtf8(""))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(20, 0, 500, 149))
        self.label_2.setLineWidth(6)
        self.label_2.setText(_fromUtf8(""))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(30, 190, 81, 81))
        self.label_3.setText(_fromUtf8(""))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.label_4 = QtGui.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(150, 190, 81, 81))
        self.label_4.setText(_fromUtf8(""))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.label_5 = QtGui.QLabel(Dialog)
        self.label_5.setGeometry(QtCore.QRect(270, 190, 81, 81))
        self.label_5.setText(_fromUtf8(""))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(Dialog)
        self.label_6.setGeometry(QtCore.QRect(390, 190, 81, 81))
        self.label_6.setText(_fromUtf8(""))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        ################################################################################
        self.label_7 = QtGui.QLabel(Dialog)
        self.label_7.setGeometry(QtCore.QRect(10, 280, 111, 41))
        self.label_7.setTextFormat(QtCore.Qt.RichText)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setWordWrap(True)
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_8 = QtGui.QLabel(Dialog)
        self.label_8.setGeometry(QtCore.QRect(140, 270, 111, 41))
        self.label_8.setTextFormat(QtCore.Qt.RichText)
        self.label_8.setAlignment(QtCore.Qt.AlignCenter)
        self.label_8.setWordWrap(True)
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.label_9 = QtGui.QLabel(Dialog)
        self.label_9.setGeometry(QtCore.QRect(260, 280, 111, 41))
        self.label_9.setTextFormat(QtCore.Qt.RichText)
        self.label_9.setAlignment(QtCore.Qt.AlignCenter)
        self.label_9.setWordWrap(True)
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.label_10 = QtGui.QLabel(Dialog)
        self.label_10.setGeometry(QtCore.QRect(380, 270, 111, 41))
        self.label_10.setTextFormat(QtCore.Qt.RichText)
        self.label_10.setAlignment(QtCore.Qt.AlignCenter)
        self.label_10.setWordWrap(True)
        self.label_10.setObjectName(_fromUtf8("label_10"))
        #################################################################3
        self.label.setPixmap(QtGui.QPixmap('res/back1.jpg'))
        self.label_2.setPixmap(QtGui.QPixmap('res/image3.png'))
        self.label_3.setPixmap(QtGui.QPixmap('res/bar1.png'))
        self.label_4.setPixmap(QtGui.QPixmap('res/pie.png'))
        self.label_5.setPixmap(QtGui.QPixmap('res/cloud1.png'))
        self.label_6.setPixmap(QtGui.QPixmap('res/exit.png'))

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "PClust Console", None))
        self.label_7.setText(_translate("Dialog", "VNum v/s VSize graph", None))
        self.label_8.setText(_translate("Dialog", "Density Graph", None))
        self.label_9.setText(_translate("Dialog", "Upload Data to cloud", None))
        self.label_10.setText(_translate("Dialog", "Quit", None))
        self.label_3.mousePressEvent = self.openBarGraph
        #self.label_3.mouseReleaseEvent = self.openBarGraph1
        self.label_4.mousePressEvent = self.openPieChart
        #self.label_4.mouseReleaseEvent = self.openPieChart1
        self.label_5.mousePressEvent = self.uploadData
        #self.label_5.mouseReleaseEvent = self.uploadData1
        self.label_6.mousePressEvent = self.exit
    def openBarGraph(self, event):
        showGraph1()
    #def openBarGraph1(self, event):
    def openPieChart(self, event):
        showGraph2()
    #def openPieChart1(self, event):
    def uploadData(self, event):
        saveGraph3()
        compress()
    #def uploadData1(self, event):
    def exit(self, event):
        saveGraph3()
        os.remove('src/vertexDensity.SGL')
        os.remove('src/vertexCustomClustSize')
        sys.exit(0)
