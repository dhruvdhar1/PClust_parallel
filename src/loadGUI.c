#include <python2.7/Python.h>
#include <stdio.h>
void loadGUI1(int argc, char *argv[])
{
    FILE *fp;
    Py_SetProgramName("GUI");
    Py_Initialize();
    PySys_SetArgv(argc,argv);
    fp = fopen("src/gui.py","r");
    PyRun_SimpleFile(fp, "src/gui.py");
    Py_Finalize();
}
void loadOP3(int argc, char *argv[])
{
    FILE *fp;
    //printf("%s\n",argv[0]);
    Py_SetProgramName("OP2");
    Py_Initialize();
    PySys_SetArgv(argc,argv);
    fp = fopen("src/GUI.py","r");
    PyRun_SimpleFile(fp, "src/GUI.py");
    Py_Finalize();
    fclose(fp);
}
