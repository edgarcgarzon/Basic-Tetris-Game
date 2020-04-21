#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width), screen_height(screen_height),
      grid_width(grid_width), grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Tetrom Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
f (!m_renderer) {
        SDL_Log("Unable to create accelerated renderer: %s", SDL_GetError());
        // fallback to software renderer
        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);
        if (!m_renderer) {
            SDL_Log("Unable to create software renderer: %s", SDL_GetError());
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Tetrom *tetrom, Bottom *bottom) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Draw current tetrom
  Color c = Color::GetTetromColor(tetrom->type);
  SDL_SetRenderDrawColor(sdl_renderer, c.red, c.green, c.blue, 0xFF);
  for (auto p : tetrom->GetCurrPoints()) {
    block.x = p.x * block.w;
    block.y = p.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Draw bottom
  for (int i = 0; i < grid_width; i++) {
    for (int j = 0; j < grid_height; j++) {
      if(bottom->cell(i,j).filled)
      {
        Color c = bottom->cell(i,j).color;
        SDL_SetRenderDrawColor(sdl_renderer, c.red, c.green, c.blue, 0xFF);
        block.x = i * block.w;
        block.y = j * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
      }
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Tetrom Score: " + std::to_string(score) +
                    " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
