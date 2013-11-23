'''
Created on 2013-11-22

@author: Rong Xiao
'''
import Tkinter as tk
import os
class MessageAction(tk.Tk):
    def __init__(self, msg, actions = ["OK"], timeout=60000, title='', screenName=None, baseName=None, className='Tk', useTk=1, sync=0, use=None):
        tk.Tk.__init__(self, screenName=screenName, baseName=baseName, className=className, useTk=useTk, sync=sync, use=use)
        self.title(title)
        gifpath = os.path.join(os.path.split(os.path.abspath(__file__))[0], "warning_tiny.gif")
        self.image = tk.PhotoImage(file=gifpath)
        self.label_panel = tk.Frame(self)
        self.label_panel.pack(side = tk.TOP, pady = 5)
        self.alive = True
        
        tk.Label(self.label_panel, image=self.image).pack(side=tk.LEFT, padx = 4)
        tk.Label(self.label_panel, text = msg).pack(anchor=tk.CENTER, pady=10, padx = 4)
        self.button_panel = tk.Frame(self)
        self.button_panel.pack(side = tk.BOTTOM, pady = 5)
        for a in actions:
            self.addButton(a)
        self.choice = actions[0]
        self.after(timeout, lambda: self.alive and self.destroy())

        
    def addButton(self, choice):
        b = tk.Button(self.button_panel, text=choice, border = 2, command=lambda:  self.setChoice(choice))
        b.pack(side=tk.LEFT, padx = 2)
    
    def setChoice(self, choice):
        self.choice = choice
        self.destroy()
        
    def show(self):
        self.mainloop()
        self.alive = False

        return self.choice

def showMsgActions(msg, title='', actions = ["OK"]):
    return MessageAction(msg, title=title, actions = actions).show()

if __name__ == '__main__':
    # MessageAction('Are you ok?', actions = ['No', 'Yes', 'I don\'t know']).show() # use quit might get confuse with next mainloop
    
    showMsgActions("The system is going to sleep now", actions = ['OK', 'Hibernate', 'Shutdown', 'Postpone'])
    import time
    time.sleep(60)