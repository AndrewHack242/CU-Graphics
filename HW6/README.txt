Andrew Hack, HW4

Time spent: 4 hours

compiling: make
running: ./hw6

----KEYBINDS

arrows: rotate around scene

p: swap between perspective and orthogonal

page up & page down: change dimensions of space

shift + m / m: change AA mode

numbers 1-4: change to set AA mode

esc: exit program


----CODE REUSE:
Code began as ex08

----OTHER NOTES:
I decided to investigate Anti-aliasing this week, using the Super-sampling and Multi-sampling methods as well as a combo of both.

Here are my observations:

MSAA does NOT help with smoothing textures especially when viewed from strange angles. I believe anistropic filtering is what I would need to fix that here.
SSAA does help with smoothing textures due to it literally rendering the scene at 2x quality.

SSAA does have the smoother edge lines, but it also has a blur effect that I don't really like. MSAA does *almost* as good and does not have this blur effect.

Combining MSAA and SSAA results in very smooth edges, and includes the texture smoothing of SSAA, but as a result, also includes that blur effect.

If the blur doesn't bother you and your computer can handle it, it seems like using both gives you silky smooth edges.

If the blut bothers you, MSAA is probably your best bet.