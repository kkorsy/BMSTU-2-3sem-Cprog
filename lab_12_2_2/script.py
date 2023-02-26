from tkinter import *
from tkinter.messagebox import *
from tkinter.scrolledtext import *

from ctypes import *

lib = CDLL('./libarr.so')
fill = lib.fill_fib
fill.argtypes = (POINTER(c_ulonglong), c_int)
fill.restype = None

def fill_fib(n):
    dst = (c_ulonglong * n)()
    fill(dst, n)

    return list(dst)

rm_dupl = lib.rm_duplicates
rm_dupl.argtypes = (POINTER(c_int), c_int, POINTER(c_int), POINTER(c_int))
rm_dupl.restype = c_int

def rm_duplicates(lst, size):
    n_src = len(lst)
    src = (c_int * n_src)(*lst)
    n_dst = c_int(size)
    
    if (size == 0):
        rc = rm_dupl(src, n_src, None, n_dst)
    
    dst = (c_int * n_dst.value)()
    rc = rm_dupl(src, n_src, dst, n_dst)
        
    return (list(dst)[:n_dst.value])


def hide_window():
    spn_num_elem.config(textvariable=IntVar(value=1))
    lb_fib_res.grid_forget()
    lb_fib_arr.delete(1.0, END)
    lb_fib_arr.grid_forget()
    window_fib.withdraw()
    
    ent_arr.config(textvariable=StringVar(value=""))
    rb_alloc_val.set(0)
    lb_set_res.grid_forget()
    lb_set_arr.delete(1.0, END)
    lb_set_arr.grid_forget()
    window_set.withdraw()
    window.grab_set()


def show_window():
    if (rb_task_val.get() == 0):
        window_fib.deiconify()
        window_fib.grab_set()
    elif (rb_task_val.get() == 1):
        window_set.deiconify()
        window_set.grab_set()


def check_num(event):
    try:
        n = int(spn_num_elem.get())
    except ValueError:
        hide_window()
        showerror("Error", "Введено некорректное количество элементов")
        show_window()
        return
    
    if (n < 0):
        hide_window()
        showerror("Error", "Введено некорректное количество элементов")
        show_window()
        return
    
    write_to_label(window_fib, fill_fib(n))


def check_array(event):
    try:
        arr = ent_arr.get().split()
        for i in range(len(arr)):
            arr[i] = int(arr[i])
    except ValueError:
        hide_window()
        showerror("Error", "Введены некорректные элементы")
        show_window()
        return
    
    if (rb_alloc_val.get()):
        size = 0
    else:
        size = len(arr)
    
    write_to_label(window_set, rm_duplicates(arr, size))
    
    
def write_to_label(w, arr):
    str_arr = "[ "
    for i in range(len(arr)):
        str_arr += str(arr[i]) + '\n'
    str_arr += " ]"
        
    if (w == window_fib):
        lb_fib_res.grid()
        lb_fib_arr.configure(state='normal')
        lb_fib_arr.delete(1.0, END)
        lb_fib_arr.insert(1.0, str_arr)
        lb_fib_arr.configure(state='disabled')
        lb_fib_arr.grid()
    else:
        lb_set_res.grid()
        lb_set_arr.configure(state='normal')
        lb_set_arr.delete(1.0, END)
        lb_set_arr.insert(1.0, str_arr)
        lb_set_arr.configure(state='disabled')
        lb_set_arr.grid()


window = Tk()
window.title("Main")
window.geometry("800x400+500+150")
window.resizable(width=0, height=0)
window.config(bg="lavender")

lb_main = Label(window, text="Работа с динамической библиотекой", font="Georgia 14", bg="lavender")
lb_main.grid(row=0, column=0, padx=125, pady=10)

frm_task = LabelFrame(window, text="Выберите задание:", font="Georgia 14", bg="floral white", relief=SUNKEN)
frm_task.grid(sticky=EW, padx=20, pady=5, row=1, column=0, rowspan=3)

rb_task_val = IntVar()
rb_task_val.set(0)
rb_task1 = Radiobutton(frm_task, text="Заполнить массив числами Фибоначчи", font="Georgia 12", bg="floral white",\
    variable=rb_task_val, value=0)
rb_task2 = Radiobutton(frm_task, text="Заполнить массив первыми вхождениями элементов исходного массива", bg="floral white",\
    font="Georgia 12", variable=rb_task_val, value=1)
rb_task1.grid(row=0, column=0, sticky=W)
rb_task2.grid(row=1, column=0, sticky=W)


btn_go = Button(window, text="Click", font="Georgia 12", bg="grey82", width=25, height=1, bd=3, command=show_window)
btn_go.grid(row=6, column=0, pady=10)


window_fib = Toplevel()
window_fib.title("Fib")
window_fib.geometry("800x400+500+150")
window_fib.config(bg="lavender")
window_fib.resizable(width=0, height=0)
window_fib.protocol("WM_DELETE_WINDOW", hide_window)

lb_fib = Label(window_fib, text="Заполнить массив числами Фибоначчи", font="Georgia 14", bg="lavender")
lb_fib.grid(row=0, column=0, padx=125, pady=5)

frm_num_elem = LabelFrame(window_fib, text="Введите количество элементов:", font="Georgia 12", bg="floral white")
frm_num_elem.grid(sticky=EW, padx=20, pady=5, row=1, column=0, rowspan=2)

spn_num_elem = Spinbox(frm_num_elem, font="Georgia 20", from_=1, to=1000000)
spn_num_elem.focus_force()
spn_num_elem.bind("<Return>", check_num)
spn_num_elem.grid(row=0, column=0, padx=10, pady=5)

lb_fib_res = Label(window_fib, text="Результат: ", font="Georgia 14", bg="lavender")
lb_fib_res.grid(sticky=W, row=3, column=0, padx=10, pady=5)
lb_fib_res.grid_forget()
lb_fib_arr = ScrolledText(window_fib, font="Impact 14", bg="white", wrap="word")
lb_fib_arr.configure(width=50, height=10)
lb_fib_arr.grid(sticky=W, row=4, column=0, padx=10, pady=5)
lb_fib_arr.grid_forget()

window_fib.withdraw()


window_set = Toplevel()
window_set.title("Set")
window_set.geometry("800x400+500+150")
window_set.config(bg="lavender")
window_set.resizable(width=0, height=0)
window_set.protocol("WM_DELETE_WINDOW", hide_window)

lb_set = Label(window_set, text="Заполнить массив первыми вхождениями\nэлементов исходного массива", font="Georgia 14", bg="lavender")
lb_set.grid(row=0, column=0, padx=100, pady=5, rowspan=2)

frm_arr = LabelFrame(window_set, text="Введите элементы массива через пробел:", font="Georgia 12", bg="floral white")
frm_arr.grid(sticky=EW, padx=20, pady=5, row=2, column=0, rowspan=2)

ent_arr = Entry(frm_arr, width=30, font="Georgia 20")
ent_arr.focus_force()
ent_arr.bind("<Return>", check_array)
ent_arr.grid(row=0, column=0, sticky=W, padx=10, pady=5)

frm_alloc = LabelFrame(window_set, text="Выберите способ выделения памяти:", font="Georgia 14", bg="floral white", relief=SUNKEN)
frm_alloc.grid(sticky=EW, padx=20, pady=5, row=4, column=0, rowspan=3)

rb_alloc_val = IntVar()
rb_alloc_val.set(0)
rb_alloc1 = Radiobutton(frm_alloc, text="Оценка максимального размера", font="Georgia 12", bg="floral white",\
    variable=rb_alloc_val, value=0)
rb_alloc2 = Radiobutton(frm_alloc, text="Вызов библиотечной функции для определения размера", font="Georgia 12", bg="floral white",\
    variable=rb_alloc_val, value=1)
rb_alloc1.grid(row=0, column=0, sticky=W)
rb_alloc2.grid(row=1, column=0, sticky=W)

lb_set_res = Label(window_set, text="Результат: ", font="Georgia 14", bg="lavender")
lb_set_res.grid(sticky=W, row=7, column=0, padx=10, pady=5)
lb_set_res.grid_forget()
lb_set_arr = ScrolledText(window_set, font="Impact 14", bg="white", wrap="word")
lb_set_arr.configure(width=50, height=5)
lb_set_arr.grid(sticky=W, row=4, column=0, padx=10, pady=5)
lb_set_arr.grid_forget()

window_set.withdraw()


window.mainloop()
