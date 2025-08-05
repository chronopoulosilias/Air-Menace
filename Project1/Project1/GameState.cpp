#include "gamestate.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Bomber.h"
#include "Kamikazi.h"
#include "Battleship.h"
#include "ScreenLevel.h"
#include "Protect_ally_level.h"

void GameState::init()
{
	graphics::setFont(getFullAssetPath("Font2.otf")); /*Fond*/
	graphics::playSound(getFullAssetPath("war.mp3"), 0.05);	/*Music*/
	m_current_screenlevel = new ScreenLevel("START");	/*A class for start,retry and end screen*/
	
	m_player = new Player("Player");	/*PLayer initialized*/
	m_player->init();

	graphics::preloadBitmaps(getAssetDir());
}

void GameState::draw()
{
	if (m_current_screenlevel) {
		m_current_screenlevel->draw();
		
	}
	if (m_current_level) {
		m_current_level->draw();
	}
}

void GameState::update(float dt)
{
	if (dt > 500) {
		return;
	}

	In_menu(dt);
	player_playing(dt);
	
	

	m_debugging = graphics::getKeyState(graphics::SCANCODE_0); /*IF player presses 0-> debug mode*/
}


std::string GameState::getAssetDir()
{
	return m_asset_path;
}

std::string GameState::getFullAssetPath(const std::string& asset)
{
	return m_asset_path + asset;
}

GameState* GameState::getInstance()
{
	if (m_unique_instance == nullptr) {
		m_unique_instance = new GameState();
	}
	return m_unique_instance;
}

void GameState::begin_playing()
{	/*This func is when the player starts to play or has lost and plays from the start*/
	total_score = 0;
	m_current_level = new Level(1);
	m_current_screenlevel->setMode("PLAYING");
	m_current_level->init();
	playing = true;
	in_menu = false;
}

void GameState::In_menu(float dt)
{
	if (in_menu) {
		m_current_screenlevel->update(dt);
		/*If the player press a button to proceed to playing*/
		if (m_current_screenlevel->passed()) {
			begin_playing();
		}
	}
}

void GameState::player_playing(float dt)
{
	if (playing) {
			m_current_level->update(dt);
			if (m_current_level->level_has_failed()) {
				/*PLayer has lost*/
				graphics::playSound(getFullAssetPath("lost.mp3"), 0.8f);
				m_current_screenlevel->setMode("RETRY");
				delete m_current_level;
				m_current_level = nullptr;
				m_player->ressurect();
				playing = false;
				in_menu = true;

			}
			else if (m_current_level->level_has_passed()) {
				/*The player has won the level so add the level_index*/
				int level_passed_index = m_current_level->get_level_index();
				m_player->regain_max_health();
				m_player->lose_powerups();

				if (level_passed_index == 4) {
					/*if index is 4 the player has won the game so display end screen*/
					graphics::playSound(getFullAssetPath("victory.mp3"), 0.8f);
					m_current_screenlevel->setMode("END");
					delete m_current_level;
					m_current_level = nullptr;
					playing = false;
					in_menu = true;


				}
				else {
					if (level_passed_index == 3) {
						Level* m_new_level = new Protect_ally_level(level_passed_index + 1);
						delete m_current_level;
						m_current_level = m_new_level;
					}
					else {
						/*Load the next level and initialize it*/
						Level* m_new_level = new Level(level_passed_index + 1);
						delete m_current_level;
						m_current_level = m_new_level;
					}
					
			
					m_current_level->init();
				}

			}


		}
	
	
}

GameState::GameState()
{
}

GameState::~GameState() {
	if (m_player != nullptr) {
		delete m_player;
	}
	if (m_current_level != nullptr) {
		delete m_current_level;
	}
	if (m_current_screenlevel != nullptr) {
		delete m_current_screenlevel;
	}
}


GameState* GameState::m_unique_instance = nullptr;