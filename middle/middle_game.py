import os
import sys
import random
import pygame
import time
import button

# pygame 설정
os.environ["SDL_VIDEO_CENTERED"] = "1"
pygame.init()



# 플레이어 생성
class Player(object):
    
    def __init__(self):
        self.rect = pygame.Rect(30,30,10,10)
        pygame.mixer.init()
 
    def move(self, dx, dy):
        
        # Move each axis separately. Note that this checks for collisions both times.
        if dx != 0:
            self.move_single_axis(dx, 0)
        if dy != 0:
            self.move_single_axis(0, dy)
    
    def original(self):
        self.rect = pygame.Rect(30,30,10,10)

    def move_single_axis(self, dx, dy):
        
        # Move the rect
        self.rect.x += dx
        self.rect.y += dy
 
        # If you collide with a wall, move out based on velocity
        for wall in walls:
            if self.rect.colliderect(wall.rect):
                if dx > 0: # Moving right; Hit the left side of the wall
                    self.rect.right = wall.rect.left
                if dx < 0: # Moving left; Hit the right side of the wall
                    self.rect.left = wall.rect.right
                if dy > 0: # Moving down; Hit the top side of the wall
                    self.rect.bottom = wall.rect.top
                if dy < 0: # Moving up; Hit the bottom side of the wall
                    self.rect.top = wall.rect.bottom
                hit_sound = pygame.mixer.Sound("hit.wav")
                pygame.mixer.Sound.play(hit_sound)
 
# 벽 class
class Wall(object):
    
    def __init__(self, pos):
        walls.append(self)
        self.rect = pygame.Rect(pos[0], pos[1], 15, 15)
 


# 화면설정
pygame.display.set_caption("Maze game!")
screen_width = 780
screen_height = 560
screen = pygame.display.set_mode((screen_width, screen_height))
white = [255,255,255]
Green = [100, 230, 100]
black = [0,0,0]
screen.fill(white) 
pygame.display.update()

clock = pygame.time.Clock()
walls = [] 
 
# 레벨별 미로만들기
level_1 = [
    "                                                       ",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    " W                  W                                 W",
    " W                  W                                 W",
    " W  WWWWWWWW  WWWW  WWWWWWWWWW  WWWWWWWWWWWWWWWWWWWW  W",
    " W  W      W  W  W           W  W                  W  W",
    " W  WWWWW  W  W  W           W  W  WWWWWWW  WWWWWWWW  W",
    " W         W  W     WWWWWWW     W       EW            W",
    " W         W  W     W           WWWWWWWWWW            W",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
]
level_2 = [
    "                                                      ",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    " W                       W           W                W",
    " W                       W  WWWWWwWWWWWWWWWWWW WWWWWW W",
    " W  WWWWWWWWWWW  WWWWWW  W  W                W W  W W W",
    " W  W         W  W    W     W  W  WWWWWWW WWWW W  W W W",
    " W  W  WWWW   W  W    WWWWWWWWWW             W W  W W W",
    " W  W  W      W  W             W   W  WWWWW  W W  WWW W",
    " W  W  W      W          WWWWWWW   W      W    W      W",
    " W  WWWW  WWWWWWWWWWWW             WWWWWWWWWWWWWWWWW  W",
    " W                   W  W   WWWWWWWW          W  W    W",
    " W                   W  W          WWWWWW  W  W  W    W",
    " WWWWWWWWWWWW  WWWWWWWWWW  WWWWWWWWW    W  W  W  W    W",
    " W          W  W  W     W  W       W    W  WWWW  W    W",
    " W     W    W  W  W  W  W  W  E    W    W  W     W WWWW",
    " WWWW    W  W  W  W  W  W  W            WWWWWWWWWWWW  W",
    " W       W  W  W  WWWW  W  WWWWWWWWWWW       W     W  W",
    " WWWWWW  W              W                    W     W  W",
    " W       W              W    W  WWWWWWWWWWW  W  W  W  W",
    " W       WWWWWWWWWWWW   W    W  W      W  W  W  W  W  W",
    " W  WWWWWW              WWWWWW  WWWWWWWW  W  W  W  W  W",
    " W       W                   W         W  W     W     W",
    " W       WWWWWWWWWWWW        W         W  W     W     W",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
]

level_4 = [
    "                                                      ",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    " W   W                W W            W                W",
    " W         WWWWWWW WWWW W  WWWWWW WWWWWWWWWWWW WWWWWW W",
    " W  WWWWW        W      W  W                 W W  W W W",
    " W  W         W  WWWWWW W  W   W  WWWWWWW WWWW W  W W W",
    " W  W WWWWW   W       W WWWWWWWW             W W  W W W",
    " W  W W   W W WWWWWWWWW        W   W  WWWWW  W W  WWW W",
    " W  W W   W W W          WWWWWWW   W      W    W      W",
    " W  WWW WWW W    WWWWWWW           WWWWWWWWWWWWWWWWW  W",
    " W      W   W     W       WWWWWWW            W     W  W",
    " WWWW  WW   WWWWWW      W        WWWWWWWWWW  W   W W  W",
    " W W    W               W  WWWW  W     W     W   W W  W",
    " W W   WWWWWWWWWWWWWWW  W     W  WWWW  W WWWWW   W    W",
    " W     W        W    W  W  WWWW  W     W W       W WWWW",
    " WWWW    WWWW        W  W  W             WW WWWWWW    W",
    " W       W  WWWWWWWWWWWWW  WWWWWWW  WWWW  W      WWWWWW",
    " WWWWWW  W              W              W  W W         W",
    " W       WWWWWWWWWWWWWWWWW   W   WWWW  WWWW W   W     W",
    " W  WWWW   W     W       W   W      W  W    W   WWWWWWW",
    " W   W        WWWWWWWWW  WWWWW   W  W  W  WWW         W",
    " W WWW  WWWW    W        W   W   WWWWWWW  WWWWWWWWWWWWW",
    " W   W     W    W  WWWWW W   W         W      W     W W",
    " W   W     W   WWW W   W W WWWWWW  WWWWWWWWW  W  W  W W",
    " W   WWW WWW   W W W W W   W             W    W  W  W W",
    " W     W   W   W W   W W   W WWWWWWWWWWWWWWWW W  W  W W",
    " WWW   W  WWWWWW W   W W W W W           W       W    W",
    " W W W    W          W   W W W W W WWW WWWWWWWWWWWWWW W",
    " W W W WWWW  WWWWWW  WWWWW W W W W W W W    W         W",
    " W   W W  W       W  W     W W W W W W W E  WWW  WWW  W",
    " W   W W  W  WWWWWW  W  W  WWWWW   W W W  W      W W  W",
    " W   W               W  W          W      W      W W  W",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
]
level_3=[
    "                                                      ",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
    " W                      W           WWWWWWWWWWWWWWWWWWW",
    " W  WWWWWWWWWWWWWWWWWW  W WWW WWWWW W                 W",
    " W  W                   W W W W     W WWWWWWWWWWW WWW W",
    " W  WWWWWWWWWWWWWWWWWWW W W W W WWWWWWWWWWW WWWWW W W W",
    " W  W   W     WWWWWWWWW W W W W           W W     W   W",
    " W  WWW W WWW W       W W   W WWWWWWWWWWW W WWWWW WWWWW",
    " W      W W W W WWWWW W WWWWW W           W W         W",
    " W      W W W W W     W       W WWW WWWWW W W WWWWWWW W",
    " W  WWWWW W W W WWWWWWW WWWWWWW WWW W     W W         W",
    " W        W W W         W         W W WWWWWWWWWWWWWWW W",
    " W  WWWWWWW W WWWWWWWWWWWW WWWW W W W W     W         W",
    " W  W              W       WWWW W W W W  WW WWWWWWWWW W",
    " W  W WWWWWWWWWWWW WWWWWWWWWWWWWW W W WWWWW           W",
    " W  W W      W   W W              W W       WWWWWWWWWWW",
    " W  W W WWWW WWW W WWWWWWWWWWWWWWWWWWWWWWWWWW         W",
    " W  W W    W W   W W                        W WWWWWWWWW",
    " W  W WWWWWW WWW W W WWWWWWWWWWWWWWWWWWW W  W         W",
    " WWWW        W   W W       W E           W  W WWWWW W W",
    " W  WWWWWWWWWWWW W WWWWWWWWWWWWWWWWWWWWWWW  W W   W W W",
    " W  W              W                     W  W   W W W W",
    " W  W  WWWWWWWWWWWWW                     W  WWWWW W W W",
    " W  W  W  WWWWWWWWWWWWWWWWWWWWWW  W WWWW W        W W W",
    " W  W  W  W                    W  W W  W WWWWWWWWWWWW W",
    " WWWW  W  W WWWWWWWW WWWWWWWWW W  W W                 W",
    " W     W  W        W        WW W  W WWWWWWWWWWWWWWWWW W",
    " W  WWWW  WWWWWWWWWWWWWWWWWWWW W  W       WWWWWW    W W",
    " W  W                     WWWW WWWW WWWWW W    W W  W W",
    " W  W WWWW WWWWWWWWWWWWWW W         W     W WW W W  W W",
    " W  W W  W W              WWWWWWWWW WWWWWWW WW W WWWW W",
    " W  W    W W              WWWWWWWWW         WW W      W",
    " W  WWWWWW WWWWWWWWWWWWWW WWWWWWWWWWWWWWWWWWWW WWWWWWWW",
    " W                  W            W                    W",
    " WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",

]

# 레벨 문자열 분석. W = wall, E = exit
def level_one():
    x = y = 0
    walls.clear()
    for row in level_1:
        for col in row:
            if col == "W":
                Wall((x, y))
            if col == "E":
                end_rect = pygame.Rect(x, y, 14, 14)
            x += 14
        y += 14
        x = 0
    return end_rect
def level_two():
    x = y = 0
    walls.clear()
    for row in level_2:
        for col in row:
            if col == "W":
                Wall((x, y))
            if col == "E":
                end_rect = pygame.Rect(x, y, 14, 14)
            x += 14
        y += 14
        x = 0
    return end_rect
def level_three():
    x = y = 0
    walls.clear()
    for row in level_3:
        for col in row:
            if col == "W":
                Wall((x, y))
            if col == "E":
                end_rect = pygame.Rect(x, y, 14, 14)
            x += 14
        y += 14
        x = 0
    return end_rect

def level_four():
    x = y = 0
    walls.clear()
    for row in level_4:
        for col in row:
            if col == "W":
                Wall((x, y))
            if col == "E":
                end_rect = pygame.Rect(x, y, 14, 14)
            x += 14
        y += 14
        x = 0
    return end_rect

#이미지
running = True
titleImg = pygame.image.load("maze1.png")
titleImg = pygame.transform.scale(titleImg,(700, 800))
startImg = pygame.image.load("start2.png").convert_alpha()
backImg = pygame.image.load("back.png").convert_alpha()
quitImg = pygame.image.load("quit.png").convert_alpha()
lv_1Img = pygame.image.load("lv_1.png").convert_alpha()
lv_2Img = pygame.image.load("lv_2.png").convert_alpha()
lv_3Img = pygame.image.load("lv_3.png").convert_alpha()
lv_4Img = pygame.image.load("lv_4.png").convert_alpha()
mazeImg = pygame.image.load("green.png")
mazeImg = pygame.transform.scale(mazeImg, (500,500))
mazeImg = pygame.transform.rotate(mazeImg, 30)
maze2Img = pygame.image.load("blue.png")
maze2Img = pygame.transform.scale(maze2Img, (450,450))
maze2Img = pygame.transform.rotate(maze2Img, 20)
timeoutImg = pygame.image.load("timeout.png")
timeoutImg = pygame.transform.scale(timeoutImg, (500,250))
clearImg = pygame.image.load("clear.png")
clearImg = pygame.transform.scale(clearImg, (500,200))

#버튼
start_button = button.Button(100,370, startImg, 0.8)
quit_button = button.Button(450, 370, quitImg, 0.8)
back_button = button.Button(600, 500, backImg, 0.6)
lv_1_button = button.Button(300, 100, lv_1Img, 0.7)
lv_2_button = button.Button(300, 200, lv_2Img, 0.7)
lv_3_button = button.Button(300, 300, lv_3Img, 0.7)
lv_4_button = button.Button(300, 400, lv_4Img, 0.7)

#타이머
total_time = 100
game_font = pygame.font.SysFont("Bahnschrift", 40)

#게임종료
def quitgame():
    pygame.quit()
    sys.exit()

#메인메뉴
def mainmenu():
    menu = True
    
    while menu:
        screen.fill(black)
        
        screen.blit(mazeImg, (-190,-200))
        screen.blit(titleImg, (25, -100))
        click_sound = pygame.mixer.Sound("b_click.wav")
        if start_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('START')
            pygame.time.delay(150)
            levelmenu()
        if quit_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('QUIT')
            pygame.time.delay(100)
            quitgame()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        
        
        pygame.display.update()

#레벨 메뉴
def levelmenu():
    menu = True

    
    while menu:
        screen.fill(black)
        screen.blit(maze2Img, (-20,-50))
        click_sound = pygame.mixer.Sound("b_click.wav")
        if lv_1_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('level 1 START')
            pygame.time.delay(150)
            maingame(1)

        if lv_2_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('level 2 START')
            pygame.time.delay(150)
            maingame(2)
        if lv_3_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('lelvel 3 START')
            pygame.time.delay(150)
            maingame(3)
        if lv_4_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('level 4 START')
            pygame.time.delay(150)
            maingame(4)

        if back_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('BACK')
            pygame.time.delay(150)
            mainmenu()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        
        
        pygame.display.update()

#게임 배경음악        
game_bgm = pygame.mixer.Sound("mainbgm.wav")
pygame.mixer.Sound.play(game_bgm)
game_bgm.play(-1)

#메인게임
def maingame(step):
    if(step == 1):
        end_rect = level_one()
    elif(step == 2):
        end_rect = level_two()
    elif(step== 3):
        end_rect = level_three()
    elif(step == 4):
        end_rect = level_four()
    
    running = True
    start_ticks = pygame.time.get_ticks()
    player = Player()
    click_sound = pygame.mixer.Sound("b_click.wav")
    finish_sound = pygame.mixer.Sound("finish.wav")
    fail_sound = pygame.mixer.Sound("fail.wav")
    while running:
        pygame.display.flip()
        clock.tick(60)
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                running = False
            if e.type == pygame.KEYDOWN and e.key == pygame.K_ESCAPE:
                running = False
 
        # Move the player if an arrow key is pressed
        key = pygame.key.get_pressed()
        if key[pygame.K_LEFT]:
            player.move(-2, 0)
        if key[pygame.K_RIGHT]:
            player.move(2, 0)
        if key[pygame.K_UP]:
            player.move(0, -2)
        if key[pygame.K_DOWN]:
            player.move(0, 2)
 
        # Just added this to make it slightly fun ;)
        if player.rect.colliderect(end_rect):
            game_bgm.stop()
            pygame.mixer.Sound.play(finish_sound)
            print("CLEAR")
            screen.fill((0,0,0))
            screen.blit(clearImg, (140, 150))
            pygame.display.flip()
            pygame.time.delay(3000)
            game_bgm.play(-1)
            mainmenu()
 
        # Draw the scene
        screen.fill((0, 0, 0))
        for wall in walls:
            pygame.draw.rect(screen, black, wall.rect)
            pygame.draw.rect(screen, (255, 0, 0), end_rect)
            pygame.draw.rect(screen, (255, 200, 0), player.rect)
        # gfxdraw.filled_circle(screen, 255, 200, 5, (0,128,0))

        elapsed_time = (pygame.time.get_ticks()-start_ticks)/1000

        timer = game_font.render("Timer: "+str(int(total_time - elapsed_time)), True, (255,255,255))
        
        screen.blit(timer, (10, 500))

        if back_button.draw(screen):
            pygame.mixer.Sound.play(click_sound)
            print('BACK')
            pygame.time.delay(150)
            levelmenu()

        if total_time - elapsed_time <= 0:
            game_bgm.stop()
            pygame.mixer.Sound.play(fail_sound)
            screen.fill((0,0,0))
            screen.blit(timeoutImg, (150, 150))
            pygame.display.flip()
            print("TIMEOUT")
            pygame.time.delay(5000)
            game_bgm.play(-1)
            mainmenu()

        pygame.display.flip()
        clock.tick(360)

def play_game():
    while True:
        mainmenu()
        pygame.display.update()


play_game()
 
pygame.quit()
