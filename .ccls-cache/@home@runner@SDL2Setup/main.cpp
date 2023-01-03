#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main(int argc, char** argv) {
  // Inicjalizuj SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Stwórz okno o szerokości 640 i wysokości 480
  SDL_Window* window = SDL_CreateWindow("Moja gra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

  // Stwórz renderer do wyświetlania grafiki
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  // Stwórz czcionkę TTF o rozmiarze 24 punktów
  TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
  if (font == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Nie można załadować czcionki: %s", TTF_GetError());
    return 1;
  }

  // Stwórz kolor czerwony
  SDL_Color red = {255, 0, 0, 255};

  // Stwórz powierzchnię tekstu
  SDL_Surface* surface = TTF_RenderText_Solid(font, "Witaj w mojej grze!", red);
  if (surface == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Nie można stworzyć powierzchni tekstu: %s", TTF_GetError());
    return 1;
  }

  // Stwórz teksturę z powierzchni tekstu
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Nie można stworzyć tekstury: %s", SDL_GetError());
    return 1;
  }

  // Zwolnij powierzchnię tekstu, ponieważ już nie jest potrzebna
  SDL_FreeSurface(surface);

  // Pętla główna gry
  bool done = false;
  while (!done) {
    // Pobierz najświeższe zdarzenie
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      // Jeśli zdarzenie to zamknięcie okna, zakończ pętl
      if (event.type == SDL_QUIT) {
        done = true;
      }
    }

    // Wyczyść ekran na kolor biały
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Wyświetl teksturę z tekstem w środku okna
    SDL_Rect dest;
    dest.x = (640 - surface->w) / 2;
    dest.y = (480 - surface->h) / 2;
    dest.w = surface->w;
    dest.h = surface->h;
    SDL_RenderCopy(renderer, texture, nullptr, &dest);

    // Wyświetl wszystko na ekranie
    SDL_RenderPresent(renderer);
  }

  // Zwolnij zasoby
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();

  return 0;
}
