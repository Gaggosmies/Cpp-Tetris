import pygame
import random

# Initialize Pygame
pygame.init()

# Screen dimensions
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600
GRID_SIZE = 30
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE

# Colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GRAY = (128, 128, 128)
COLORS = [
    (0, 255, 255),
    (0, 0, 255),
    (128, 0, 128),
    (255, 165, 0),
    (255, 255, 0),
    (0, 128, 0),
    (255, 0, 0),
]

# Tetromino shapes
SHAPES = [
    [[1, 1, 1, 1]],  # I
    [[1, 1, 1], [0, 1, 0]],  # T
    [[0, 1, 1], [1, 1, 0]],  # S
    [[1, 1, 0], [0, 1, 1]],  # Z
    [[1, 1], [1, 1]],  # O
    [[1, 1, 1], [1, 0, 0]],  # L
    [[1, 1, 1], [0, 0, 1]],  # J
]

# Main game class
class Tetris:
    def __init__(self):
        self.width = GRID_WIDTH
        self.height = GRID_HEIGHT
        self.board = [[0 for _ in range(self.width)] for _ in range(self.height)]
        self.score = 0
        self.state = "start"
        self.piece = None
        self.next_piece = self.new_piece()

    def new_piece(self):
        piece_shape = random.choice(SHAPES)
        color = random.choice(COLORS)
        piece = {'shape': piece_shape, 'color': color, 'x': GRID_WIDTH // 2 - len(piece_shape[0]) // 2, 'y': 0}
        return piece

    def intersects(self):
        for i in range(len(self.piece['shape'])):
            for j in range(len(self.piece['shape'][i])):
                if self.piece['shape'][i][j] > 0:
                    if i + self.piece['y'] > self.height - 1 or \
                       j + self.piece['x'] > self.width - 1 or \
                       j + self.piece['x'] < 0 or \
                       self.board[i + self.piece['y']][j + self.piece['x']] > 0:
                        return True
        return False

    def freeze_piece(self):
        for i in range(len(self.piece['shape'])):
            for j in range(len(self.piece['shape'][i])):
                if self.piece['shape'][i][j] > 0:
                    self.board[i + self.piece['y']][j + self.piece['x']] = self.piece['color']
        self.clear_lines()
        self.score += 10
        self.piece = None

    def clear_lines(self):
        lines_to_clear = []
        for i, row in enumerate(self.board):
            if 0 not in row:
                lines_to_clear.append(i)
        for i in lines_to_clear:
            del self.board[i]
            self.board.insert(0, [0 for _ in range(self.width)])
        self.score += 100 * len(lines_to_clear)

    def rotate_piece(self):
        if self.piece is None:
            return
        new_shape = list(zip(*self.piece['shape'][::-1]))
        old_piece = self.piece
        self.piece['shape'] = new_shape
        if self.intersects():
            self.piece = old_piece

    def move_piece(self, dx, dy):
        if self.piece is None:
            return
        self.piece['x'] += dx
        self.piece['y'] += dy
        if self.intersects():
            self.piece['x'] -= dx
            self.piece['y'] -= dy
            if dy > 0:  # The piece has landed
                self.freeze_piece()

    def step(self):
        self.move_piece(0, 1)

# Pygame loop
def run_game():
    game = Tetris()
    clock = pygame.time.Clock()
    running = True

    while running:
        if game.state == "gameover":
            running = False

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    game.rotate_piece()
                if event.key == pygame.K_DOWN:
                    game.move_piece(0, 1)
                if event.key == pygame.K_LEFT:
                    game.move_piece(-1, 0)
                if event.key == pygame.K_RIGHT:
                    game.move_piece(1, 0)
                if event.key == pygame.K_SPACE:
                    while not game.intersects():
                        game.move_piece(0, 1)
                    game.freeze_piece()

        screen.fill(BLACK)

        if game.piece is None:
            game.piece = game.next_piece
            game.next_piece = game.new_piece()
            if game.intersects():
                game.state = "gameover"

        game.step()

        # Draw the board
        for i in range(game.height):
            for j in range(game.width):
                if game.board[i][j] != 0:
                    pygame.draw.rect(screen, game.board[i][j], (j * GRID_SIZE, i * GRID_SIZE, GRID_SIZE, GRID_SIZE))
        
        # Draw the current piece
        if game.piece:
            for i in range(len(game.piece['shape'])):
                for j in range(len(game.piece['shape'][i])):
                    if game.piece['shape'][i][j] != 0:
                        pygame.draw.rect(screen, game.piece['color'],
                                         (int((game.piece['x'] + j) * GRID_SIZE), int((game.piece['y'] + i) * GRID_SIZE),
                                          GRID_SIZE, GRID_SIZE))
        
        # Display score
        font = pygame.font.SysFont('Arial', 25, True)
        score_text = font.render(f'Score: {game.score}', True, WHITE)
        screen.blit(score_text, [0, 0])

        pygame.display.flip()
        clock.tick(10)

    pygame.quit()

if __name__ == "__main__":
    screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
    pygame.display.set_caption('Tetris')
    run_game()
