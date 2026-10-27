import turtle

screen = turtle.Screen()
screen.bgcolor("black")
t = turtle.Turtle()
t.speed(0)
t.color("cyan")

for i in range(360):
    t.forward(i)
    t.left(59)

screen.mainloop()