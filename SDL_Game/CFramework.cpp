//********************************************************************
//*                                                                  *
//*                      K l a s s e    CFramework                   *
//*                                                                  *
//********************************************************************
//*                                                                  *
//*                      Dateiname   CFramework.cpp                  *
//*                                                                  *
//********************************************************************
//*                                                                  *
//* Aufgabe: Diese Klasse sorgt daf�r, dass die SDL initialisiert    *
//*          und wieder heruntergefahren wird. Alle im Spiel         *
//*          gerenderten(gezeichneten) Objekte werden hier dann      *
//*          entg�ltig auf den Bildschirm gebracht (dazu sp�ter      *
//*          eine genauere Erkl�rung). Ausserdem wird hier der       *
//*          spielinterne Zeitgeber (Timer) aktualisiert sowie der   *
//*          aktuelle Status der Tastatur abgefragt.                 *
//*                                                                  *
//********************************************************************
//
// Todo umbenennen in CFramework.cpp
// Todo Erkl�rung erweitern
//
//
#include "CFramework.hpp"
#include <iostream>
#include <fstream>
//
// Konstruktor
//
// Aufgabe: Allgemeine Initialisierungen
//
CFramework::CFramework()
{
	m_pWindow = NULL;
	m_pRenderer = NULL;
	m_pKeystate = NULL;

} // Konstruktor



// Init
//
// Aufgabe: Framework initialisieren
//
bool CFramework::Init(int ScreenWidth, int ScreenHeight, 
					  int ColorDepth, bool bFullscreen)
{
	// Alle Systeme der SDL initialisieren
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) == -1)
	{
		cout << "SDL konnte nicht initialisiert werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;

		Quit();

		return (false);
	}

	Uint32 WindowFlags = 0;
	
	// Vollbild oder Fenstermodus?
	if (bFullscreen == true)
		WindowFlags = SDL_WINDOW_FULLSCREEN;
	else
		WindowFlags = SDL_WINDOW_SHOWN;
	

	m_pWindow = SDL_CreateWindow("Asteroid",
								200, //SDL_WINDOWPOS_UNDEFINED,
								200, //SDL_WINDOWPOS_UNDEFINED,
								ScreenWidth,
								ScreenHeight,
								WindowFlags);

	// Pr�fen, ob alles funktioniert hat
	if (m_pWindow == NULL)
	{
		cout << "SDL_Fenster konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;
		
		Quit();
		
		return (false);
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
	
	// Pr�fen, ob alles funktioniert hat
	if (m_pRenderer == NULL)
	{
		cout << "SDL_Renderer konnte nicht erzeugt werden!" << endl;
		cout << "Fehlermeldung: " << SDL_GetError() << endl;
	
		Quit();
		
		return (false);
	}

	// Zeiger auf internes Array f�r Tastaturstatus ermitteln
	m_pKeystate = SDL_GetKeyboardState(NULL);
	
	// Alles ging glatt, also true zur�ckliefern
	return (true);

} // Init

// Quit
//
// Aufgabe: Framework (SDL) beenden
//
void CFramework::Quit()
{
	// Renderer und Fenster freigeben
	if (m_pRenderer != NULL)
	{
		SDL_DestroyRenderer(m_pRenderer);
	}
	if (m_pWindow != NULL)
	{
		SDL_DestroyWindow(m_pWindow);
	}

	// SDL beenden
	SDL_Quit();

} // Quit


// Update
//
// Aufgabe: Timer und Keyboardstatus updaten
//
void CFramework::Update()
{
	// Timer updaten
	g_pTimer->Update();

	// Tastaturstatus ermitteln
	SDL_PumpEvents();

} // Update


// Keydown
//
// Aufgabe: Tastendruck abfragen
//
bool CFramework::KeyDown(int Key_ID)
{
	// Pr�fen, ob Taste gedr�ckt ist
	//return (m_pKeystate[Key_ID] ? true : false); // tern�rer Operator
	if (m_pKeystate[Key_ID])
		return true;
	else
		return false;
// tern�rer Operator in if �ndern

} // KeyDown


// Clear
//
// Aufgabe: Buffer l�schen
//
void CFramework::Clear()
{
	// Buffer (Surface) mit Hintergrundfarbe f�llen
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	SDL_RenderClear(m_pRenderer);

} // Clear

// Render
//
// Aufgabe: Spiel rendern
//
void CFramework::Render ()
{
	// Rendern
	SDL_RenderPresent(m_pRenderer);

} // Render
