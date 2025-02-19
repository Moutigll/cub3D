### Global Variables
- `screenWidth/Height` the resolution of the window.
- **Time management**
  - `oldTime` and `newTime` to get a frame duration.
  - Used to maintain a **constant** moving speed.
- **Map** `map[h][w]` an array of array representing the map.
- **Player**
	- **FOV (Field of View)** - Determine the vision angle
	- **Position** `playerPosX/Y` - The player's coordinates on the map.
	- **Direction vector** `playerDirX/Y` - Indicates where the player is looking.
	- **Camera plane** `camPlaneX/Y` - A perpendicular vector to `playerDir` used to cast rays.
     - **Defined as:**
       ```objectivec
       double  camPlaneX = -playerDirY * FOV;
       double  camPlaneY = playerDirX * FOV;
       ```
## DDA - Raycasting Algorithm
**Goal:** For each column of pixels on the screen cast a ray and see wich block it collide with.
### **1. Compute** `cameraX`
`cameraX`  represents a horizontal coordinate on the camera plane. It varies between **-1 (left edge)** and **1 (right edge)** and determines the direction of the ray for each screen column.
  ```objectivec
  double  cameraX	2 * (XcolumnOnScreen / ScreenWidth) - 1;
  ```
### **2. Compute the** `rayDir` **vector**
This vector defines the direction in which the ray is cast. It is calculated by adding the looking direction (`playerDir`) and the corresponding offset from the camera plane.
  ```objectivec
  double  rayDirX = playerDirX + (camPlaneX * cameraX);
  double  rayDirY = playerDirY + (camPlaneY * cameraX);
  ```
**Purpose:**
- `playerDirX/Y` determines the base direction of the player's view.
- `camPlaneX/Y * cameraX` offsets the ray horizontally across the player's vision.
### **3. Init** `rayX` **and** `rayY`
The ray starts at the player's **integer grid position**.
  ```objectivec
  int  rayX = posX;
  int  rayY = posY;
  ```
**Why integers?**
- The map is a grid, so the ray needs to be positioned relative to **grid cells**.
### **4. Compute** `distX` **and** `distY`
It correspond to the **distance** to travel on the x and y axes **before intersecting with a new line** of the grid**
   - **Warning** Protect your code against divisions by zero !<br><br>
  ```objectivec
  double  distX = 1 / rayDirX;
  double  distY = 1 / rayDirY;
  ```
### **5. Compute** `step` **and** `distFromSide`
Get the direction `step` and the distance `distFromSide` before reaching a new line for the `rayDir` vector
  - **5.1 If** `rayDirX` is negative, we are going to the left<br><br>
    ```objectivec
    int  stepX = -1;
    double  distFromSideX = (rayX - posX) * distX;
    ```
    `distFromSideX` is the `distance` between the `ray` and `player` X position multiplied by the X distance of the `ray vector` on the X axe
  - **5.2 Else** we go to the right, the `distance` calcul is inverted<br><br>
    ```objectivec
    int  stepX = 1;
    double  distFromSideX = (posX + 1 - rayX) * distX;
    ```
  - **5.3 Repeat the two previous steps but for** `Y`
### **6. Perform the DDA loop**
**Goal:** get the first tile on the grid with wich the ray collide
- **6.1 We loop while the ray is on a empty tile**
```objectivec
while (map[rayY][rayX] == 0)
```
- **6.2 we check if we're closer from a X or Y line and move accordingly**
```objectivec
if (distFromSideX < distFromSideY)
{
	distFromSideX += distX;
	rayX += stepX;
}
else...
```