#!/usr/bin/env python
import tkFileDialog
from Tkinter import *
import sys
"""import image,imagetk"""


def gui():
    """make the GUI version of this command that is run if no options are
    provided on the command line"""
    def button_browse_callback():
        """ What to do when the Browse button is pressed """
        filename = tkFileDialog.askopenfilename()
        entry.delete(0, END)
        entry.insert(0, filename)

    def button_go_callback():
        """ what to do when the "ok" button is pressed """
        input_file = entry.get()
        table_contents = read_file(input_file)
        print(input_file)
        sys.exit(0)

    root = Tk()
    root.title("PClust")
    root.geometry("350x400")
    """imageFile = "DFD Pclust.png"
    img = imagetk.PhotoImage(image.open(imageFile))
    panel = tk.Label(window, image = img)
    panel.pack(side = "bottom", fill = "both", expand = "yes")"""
    frame = Frame(root)
    frame.pack()


    def save():
        input_file = entry.get()
        open("src/input.txt","w").close()
        text = w.get() + "\n" + w1.get() + "\n" + w2.get() + "\n"
        with open("src/input.txt", "a") as f:
            f.write(text)
        open("src/input.txt","a").close()
        lname = input_file.split("/")[-1]
        with open("src/input.txt", "a") as f:
            f.write(lname)
        root.destroy()

    svalue = IntVar() # defines the widget state as int
    foo = Label(root,text="No of Sequence",font=("Purisa",12))
    foo.pack()
    w = Entry(root,textvariable=svalue) # adds a textarea widget
    w.pack()

    svalue1 = IntVar() # defines the widget state as int
    foo = Label(root,text="No of Clusters",font=("Purisa",12))
    foo.pack()
    w1 = Entry(root,textvariable=svalue1) # adds a textarea widget
    w1.pack()

    svalue2 = IntVar() # defines the widget state as int
    foo = Label(root,text="No of Vertices",font=("Purisa",12))
    foo.pack()
    w2 = Entry(root,textvariable=svalue2) # adds a textarea widget
    w2.pack()

    separator = Frame(root, height=5, bd=2, relief=SUNKEN)
    separator.pack(fill=X, padx=10, pady=5)
    label = Label(root, text="File Path: ",font=("Purisa",12))
    entry = Entry(root, width=50)
    label.pack()
    entry.pack()

    button_browse = Button(root,
                           text="BROWSE",
                           command=button_browse_callback,font=("Algerian",12,'bold'),height=1, width=8, background="gray",activebackground="blue",fg="black")
    button_go = Button(root,
                       text="OK",
                       command=save,font=("Algerian",12,'bold'),height=1, width=8, background="gray",activebackground="blue",fg="black")
    button_exit = Button(root,
                         text="EXIT",
                         command=sys.exit,font=("Algerian",12,'bold'),height=1, width=8, background="gray",activebackground="blue",fg="black")
    button_browse.pack(padx=20,pady=9)
    button_go.pack(pady=9)
    button_exit.pack(side=BOTTOM,pady=9)
    separator = Frame(root, height=5, bd=2, relief=SUNKEN)
    separator.pack(fill=X, padx=3, pady=3)
    mainloop()

def command_line(args):
    """ Run the command-line version"""
    if args.output is None:
        args.output = get_output_filename(args.input)
    table_contents = read_file(args.input)
    if write_table(args.output, table_contents):
        print "rst table is in file `{}'".format(args.output)
    else:
        print "Writing file `{}' did not succeed.".format(args.output)

def read_file(filename):
     """Read the DAT file
      This fails pretty silently on any exception at all"""
     try:
        media = []
        with open("filename", "rb") as f:
          media.append(f.readlines())
        for row in media:
          media.append(row)
     except:
        return None
     return r

if __name__ == "__main__":
    gui()                   #  run the GUI version
