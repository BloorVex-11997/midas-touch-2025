<h1 align="center">
   <img src="https://github.com/BloorVex-11997/midas-touch-2025/blob/main/midas-logo.png" width=256></img>
   <br>
   Team 11997A M1DA5
</h1>
<p>
   Midas Touch - VEX V5 Robot Midas Touch is a VEX V5 robot designed for precision, agility, and versatility. Featuring omni-directional movement powered by an advanced drivetrain and a robust elevator mechanism, this robot is built to excel in dynamic competition environments. 
</p>
<p>
   Welcome to our robot code repository, which is fully open-source with many examples, well-structured code, and intuitive comments. If you have any questions, feel free to create an issue with details.
</p>
<br>
<br>
<br>


#   Project requirements
- [PROS by perdue](https://marketplace.visualstudio.com/items?itemName=sigbots.pros)
- [Visual Studio Code](https://code.visualstudio.com/download)
- MINGW or equivalent GCC/G++ compilers


## What is PROS?
PROS in an extension for VSCoed that allows us to interface between the Vex V5 robots and our computer. It lets us build and upload robot code both directly via wire and also wirelessly.


## Installation
Do the following in order:
1. Install MINGW or **equivalent** GCC/G++ compilers 
   - [MINGW Installation guide for Windows](https://www.youtube.com/watch?v=sXW2VLrQ3Bs)
   - [GCC/G++ Compiler for Mac](https://www.youtube.com/watch?v=wY24ehH6mC0)
   - If you have linux you don't need a guide figure it out
2. Install VsCode from the [website](https://code.visualstudio.com)
3. Install the PROS extension -> [PROS Perdue installation guide](https://pros.cs.purdue.edu/v5/getting-started/)


## Interfacing the robot 
Once you have finished all the pre-requisite interfacing the robot is very simple

### Robot setup
1. Plug the provided Micro USB cable into the Vex V5 brain
2. Plug the USB side into your computer
3. Wait for PROS to detect Vex v5 Brain
4. Run Brain Terminal Command to ensure proper connection

### Running code
simply head to to the PROS section of your VSCode and click 
**Build and Upload**
After that click **Run**

# Holonomic Drivetrain Math

Author: Mateo Barbosa, Safwan Ahmed <br>
Date: January 28, 2025

We can derive the following matrix equation, which shows the relationship between the speeds of the motors and the angles at which the wheels are oriented, and gives the vector $a$ which is then decomposed into $a_x, a_{y}$.

$$\begin{bmatrix}
a_{x} \\
a_{y} \\
\omega
\end{bmatrix} =
\begin{bmatrix}
\cos(\theta_{1} + \frac{\pi}{2} + \Omega) & \cos(\theta_{2} + \frac{\pi}{2} + \Omega) & \cos(\theta_{3} + \frac{\pi}{2} + \Omega) \\
\sin(\theta_{1} + \frac{\pi}{2} + \Omega) & \sin(\theta_{2} + \frac{\pi}{2} + \Omega) & \sin(\theta_{3} + \frac{\pi}{2} + \Omega) \\
1 & 1 & 1
\end{bmatrix}
\begin{bmatrix}
m_{1} \\
m_{2} \\
m_{3}
\end{bmatrix}$$

Where:

- $m_{1}, m_{2}$ and $m_{3}$ are the speeds of the motors.
- $a_{x}, a_{y}$ are the $x$ and $y$ components of the vector that represents the robot.
- $\omega$ represents the angular velocity of the motors and acts as a scalar.
- $\Omega$ represents the total angular displacement from the original rotation.
- $\theta_{1}, \theta_{2}$ and $\theta_{3}$ represent the angles at which the motors are oriented.

We take the measures of $\theta$ with one motor of the triangle facing upwards directly. The angles are measured as they would be in a system with four quadrants going counterclockwise. From this, we find $\theta_{1}, \theta_{2}$ and $\theta_{3}$ as $\frac{\pi}{6}, \frac{5\pi}{6}$ and $\frac{3\pi}{2}$ respectively.

From this, we can represent the $\cos$ and $\sin$ in terms of only $\Omega$:

$$\begin{bmatrix}
a_{x}\\
a_{y}\\
\omega
\end{bmatrix} = 
\begin{bmatrix}
\cos\left(\frac{2\pi}{3} + \Omega\right) & \cos\left(\frac{4\pi}{3} + \Omega\right) & \cos(2\pi + \Omega)\\
\sin\left(\frac{2\pi}{3} + \Omega\right) & \sin\left(\frac{4\pi}{3} + \Omega\right) & \sin(2\pi + \Omega)\\
1 & 1 & 1
\end{bmatrix}
\begin{bmatrix}
m_{1}\\
m_{2}\\
m_{3}
\end{bmatrix}$$

We aim to invert a $3\times3$ matrix to compute the relationship:

$\mathbf{a} = \mathbf{M} \cdot \mathbf{b},$

Where:

- $\mathbf{a}$ is a $3\times1$ vector of motor speeds in the form $(m_1,m_2,m_3)$ .
- $\mathbf{b}$ is a $3\times1$ vector of $(a_x, a_y,\omega)$.
- $\mathbf{M}$ is a $3\times3$ transformation matrix.

By inverting the matrix $\mathbf{M}$, we can solve for $\mathbf{b}$ in terms of $\mathbf{a}$:

$\mathbf{b} = \mathbf{M}^{-1} \cdot \mathbf{a}.$

The inverse of a $3\times3$ matrix $\mathbf{M}$ is given by:

$\mathbf{M}^{-1} = \frac{1}{\det(\mathbf{M})} \cdot \text{adj}(\mathbf{M}),$

Where:

- $\det(\mathbf{M})$ is the determinant of $\mathbf{M}$.
- The adjugate matrix $\text{adj}(\mathbf{M})$ is the transpose of the cofactor matrix, where each element is the determinant of the $2\times2$ submatrix formed by removing the corresponding row and column from $\mathbf{M}$.

After inverting, we end up with the matrix equation:

$$
\begin{bmatrix}
m_{1}\\
m_{2}\\
m_{3}
\end{bmatrix} = 
\dfrac{2}{3\sqrt{3}}
\begin{bmatrix}
\dfrac{-3\sin(\Omega)}{2} - \dfrac{\sqrt{3}\cos(\Omega)}{2} & \dfrac{3\cos(\Omega)}{2} - \dfrac{\sqrt{3}\sin(\Omega)}{2} & \dfrac{\sqrt{3}}{2}\\
\dfrac{3\sin(\Omega)}{2} - \dfrac{\sqrt{3}\cos(\Omega)}{2} & \dfrac{-3\cos(\Omega)}{2} - \dfrac{\sqrt{3}\sin(\Omega)}{2} & \dfrac{\sqrt{3}}{2}\\
\sqrt{3}\cos(\Omega) & \sqrt{3}\sin(\Omega) & \dfrac{\sqrt{3}}{2}
\end{bmatrix}
\begin{bmatrix}
a_{x}\\
a_{y}\\
\omega
\end{bmatrix}
$$

Where we can now solve for $m_{1}, m_{2}$ and $m_{3}$ by inputting the desired $a_x, a_y$ and $\omega$ respectively.







## Source

for a more in depth explanation of the math shown above [click here](https://youtu.be/ULQLD6VvXio?si=WE3N78HXeV3rWSJp)
