// Sprite.hpp
#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "CFramework.hpp" 

// Bei Wellen #include dann liegt die
// Datei nicht bei den anderen Quelldateien
class CSprite
{
	public:
		CSprite  ();
		~CSprite ();

		void Load		 (const string sFilename);
		void Load		 (const string sFilename, int NumFrames,
						  int FrameWidth, int FrameHeight);
		void SetPos		 (float fXPos, float fYPos);
		void Render		 ();
		void Render		 (float fFrameNumber);
		SDL_Rect GetRect () { return m_Rect;	}

	private:
		SDL_Renderer *m_pRenderer;	// Zeiger auf den Renderer
		SDL_Texture  *m_pImage;		// Das eigentliche Bild des Sprites
		SDL_Rect	  m_Rect;		// Rect des Sprites
		SDL_Rect	  m_FrameRect;	// Ausschnitt f�r Animationsphase
		int m_NumFrames;			// Anzahl der Animationsphasen
		int m_FrameWidth;			// Breite einer Animationsphase
		int m_FrameHeight;			// H�he einer Animationsphase
		int m_NumFramesX;			// Wie viele Anim-Phasen in X-Richtung?
}; // CSprite
#endif
