#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

#include "player.h"
#include "player_states.h"

//#include "skeleton.h"
//#include "skeleton_states.h"

#include "tiles.h"

using namespace std;


class TileWorld
{
private:

	// Размеры сетки из тайлов
	int num_tiles_x, num_tiles_y;
	int tilesize;
	
	sf::Texture tileset_texture;

	// Координаты каждого тайла на текстуре
	std::map<Tile, sf::IntRect> tile_texture_coords;

	// Сетка из ячеек (тайлов) (вектора tilegrid и decoration_tilegrid имеют размер num_tiles_x * num_tiles_y)
	// tilegrid            - непроходимые тайлы
	// decoration_tilegrid - проходимые декоративные тайлы
	std::vector<Tile> tilegrid;
	std::vector<Tile> decoration_tilegrid;

	Player player;

	//Skeleton skeleton;

	sf::Sprite tile_sprite;

	sf::View view;

	// Текстуры и спрайты для облаков и гор
	std::vector<sf::Texture> background_textures;
    std::vector<sf::Sprite> backgrounds;

	float time;
	float scale_factor;

	bool is_editor_mode;

public:

	TileWorld(unsigned int num_tiles_x, unsigned int num_tiles_y, bool is_editor_mode) 
		: num_tiles_x(num_tiles_x), num_tiles_y(num_tiles_y), is_editor_mode(is_editor_mode),
		  player(Player({0, 0})), view(sf::FloatRect(0, 0, 1200, 900)), time(0)
	{

		background_textures.resize(4);
        backgrounds.resize(4);
        background_textures[0].loadFromFile("../textures/background/CloudsBack.png");
        background_textures[1].loadFromFile("../textures/background/CloudsFront.png");
        background_textures[2].loadFromFile("../textures/background/BGBack.png");
        background_textures[3].loadFromFile("../textures/background/BGFront.png");
        for (int i = 0; i < 4; ++i)
        {
            background_textures[i].setRepeated(true);
            backgrounds[i] = sf::Sprite(background_textures[i]);
            backgrounds[i].setScale(3, 3);
        }

		tilesize = 16;
		if (!tileset_texture.loadFromFile("../textures/tileset.png"))
		{
			std::cout << "Can't load image ../textures/tileset.png for TileWorld class" << std::endl;
			exit(1);
		}
		tile_sprite.setTexture(tileset_texture);
		scale_factor = 5;
		tile_sprite.setScale(scale_factor, scale_factor);



		tile_texture_coords = {
			{Tile::TransparentWall, {64, 32, 16, 16}},
			{Tile::GroundTopLeft, {0, 0, 16, 16}},    
			{Tile::GroundTop, {16, 0, 16, 16}},     
			{Tile::GroundTopRight, {32, 0, 16, 16}},
			{Tile::GroundLeft, {0, 16, 16, 16}},       
			{Tile::GroundCenter, {16, 16, 16, 16}},  
			{Tile::GroundRight, {32, 16, 16, 16}},
			{Tile::GroundBottomLeft, {0, 32, 16, 16}}, 
			{Tile::GroundBottom, {16, 32, 16, 16}},  
			{Tile::GroundBottomRight, {32, 32, 16, 16}},
			{Tile::GroundTop2, {48, 0, 16, 16}},
			{Tile::InnerStones, {48, 16, 16, 16}},
			{Tile::InnerStones2, {48, 32, 16, 16}},
			{Tile::GroundCornerBottomRight, {96,  0, 16, 16}},
			{Tile::GroundCornerBottomLeft,  {112,  0, -16, 16}},
			{Tile::GroundCornerOpenBottomRight, {112, 0, 16, 16}},
			{Tile::GroundCornerOpenBottomLeft,  {128, 0, -16, 16}},
			{Tile::Bridge, {112, 64, 16, 16}},
			{Tile::GrassLeft, {96, 32, 16, 16}},       
			{Tile::GrassCenter, {112, 32, 16, 16}},  
			{Tile::GrassRight, {128, 32, 16, 16}},
			{Tile::Fence1, {96, 48, 16, 16}},
			{Tile::Fence2, {112, 48, 16, 16}},       
			{Tile::Fence3, {128, 48, 16, 16}},  
			{Tile::Bush1, {80, 80, 16, 16}},
			{Tile::Bush2, {96, 80, 16, 16}},
			{Tile::Bush3, {112, 80, 16, 16}},
			{Tile::Pikes, {144, 64, 16, 16}},       
			{Tile::BridgeStart, {96, 64, 16, 16}},  
			{Tile::BridgeFinish, {128, 64, 16, 16}},
			{Tile::CaveCenter, {16, 64, 16, 16}},
			{Tile::CaveLeft, {0, 64, 16, 16}},

			//{Tile::Tree1_1, {160, 0, 16, 16}},
			{Tile::Tree1_2, {160, 16, 16, 16}},
			{Tile::Tree1_3, {160, 32, 16, 16}},
			{Tile::Tree1_4, {160, 48, 16, 16}},
			//{Tile::Tree1_5, {160, 64, 16, 16}},
			{Tile::Tree1_6, {176, 0, 16, 16}},
			{Tile::Tree1_7, {176, 16, 16, 16}},
			{Tile::Tree1_8, {176, 32, 16, 16}},
			{Tile::Tree1_9, {176, 48, 16, 16}},
			{Tile::Tree1_10, {176, 64, 16, 16}},
			{Tile::Tree1_11, {192, 0, 16, 16}},
			{Tile::Tree1_12, {192, 16, 16, 16}},
			{Tile::Tree1_13, {192, 32, 16, 16}},
			{Tile::Tree1_14, {192, 48, 16, 16}},
			{Tile::Tree1_15, {192, 64, 16, 16}},
			{Tile::Tree1_16, {208, 0, 16, 16}},
			{Tile::Tree1_17, {208, 16, 16, 16}},
			{Tile::Tree1_18, {208, 32, 16, 16}},
			{Tile::Tree1_19, {208, 48, 16, 16}},
			{Tile::Tree1_20, {208, 64, 16, 16}},

			//{Tile::Tree2_1, {224, 0, 16, 16}},
			{Tile::Tree2_2, {224, 16, 16, 16}},
			{Tile::Tree2_3, {224, 32, 16, 16}},
			{Tile::Tree2_4, {224, 48, 16, 16}},
			//{Tile::Tree2_5, {224, 64, 16, 16}},
			//{Tile::Tree2_6, {224, 80, 16, 16}},
			//{Tile::Tree2_7, {224, 96, 16, 16}},
			{Tile::Tree2_8, {240, 0, 16, 16}},
			{Tile::Tree2_9, {240, 16, 16, 16}},
			{Tile::Tree2_10, {240, 32, 16, 16}},
			{Tile::Tree2_11, {240, 48, 16, 16}},
			{Tile::Tree2_12, {240, 64, 16, 16}},
			{Tile::Tree2_13, {240, 80, 16, 16}},
			{Tile::Tree2_14, {240, 96, 16, 16}},
			{Tile::Tree2_15, {256, 0, 16, 16}},
			{Tile::Tree2_16, {256, 16, 16, 16}},
			{Tile::Tree2_17, {256, 32, 16, 16}},
			{Tile::Tree2_18, {256, 48, 16, 16}},
			{Tile::Tree2_19, {256, 64, 16, 16}},
			{Tile::Tree2_20, {256, 80, 16, 16}},
			{Tile::Tree2_21, {256, 96, 16, 16}},
			{Tile::Tree2_22, {272, 0, 16, 16}},
			{Tile::Tree2_23, {272, 16, 16, 16}},
			{Tile::Tree2_24, {272, 32, 16, 16}},
			{Tile::Tree2_25, {272, 48, 16, 16}},
			//{Tile::Tree2_26, {272, 64, 16, 16}},
			//{Tile::Tree2_27, {272, 80, 16, 16}},
			//{Tile::Tree2_28, {272, 96, 16, 16}},
			//{Tile::Tree2_29, {288, 0, 16, 16}},
			{Tile::Tree2_30, {288, 16, 16, 16}},
			{Tile::Tree2_31, {288, 32, 16, 16}},
			{Tile::Tree2_32, {288, 48, 16, 16}}
			//{Tile::Tree2_33, {288, 64, 16, 16}},
			//{Tile::Tree2_34, {288, 80, 16, 16}},
			//{Tile::Tree2_35, {288, 96, 16, 16}}
		};

		tilegrid.resize(num_tiles_x * num_tiles_y);
	}

	int get_tile_size()
	{
		return tilesize;
	}
	float get_tile_world_size()
	{
		return tilesize * scale_factor;
	}

	void set_tile(int x, int y, Tile new_tile)
	{
		tilegrid[x + num_tiles_x * y] = new_tile;
	}

	void set_decoration_tile(int x, int y, Tile new_tile)
	{
		decoration_tilegrid[x + num_tiles_x * y] = new_tile;
	}

	void set_window_view(sf::RenderWindow& window)
	{
		window.setView(window.getDefaultView());
	}

	void set_world_view(sf::RenderWindow& window)
	{
		window.setView(view);
	}

	void switch_camera_mode()
	{
		is_editor_mode = !is_editor_mode;
	}

	void set_view_player()
	{
		sf::Vector2f player_center = player.get_center();
		float view_move_ratio = 0.6;
		if (player_center.x > view.getCenter().x + view_move_ratio * view.getSize().x / 2)
		{
			view.move({player_center.x - view.getCenter().x - view_move_ratio * view.getSize().x / 2, 0});
		}
		else if (player_center.x < view.getCenter().x - view_move_ratio * view.getSize().x / 2)
		{
			view.move({player_center.x - view.getCenter().x + view_move_ratio * view.getSize().x / 2, 0});
		}

		if (player_center.y > view.getCenter().y + view_move_ratio * view.getSize().y / 2)
		{
			view.move({0, player_center.y - view.getCenter().y - view_move_ratio * view.getSize().y / 2});
		}
		else if (player_center.y < view.getCenter().y - view_move_ratio * view.getSize().y / 2)
		{
			view.move({0, player_center.y - view.getCenter().y+ view_move_ratio * view.getSize().y / 2});
		}
	}

	void set_view_editor()
	{
		float editor_view_speed = 10;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			view.move({-editor_view_speed, 0});
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view.move({+editor_view_speed, 0});
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			view.move({0, +editor_view_speed});
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view.move({0, -editor_view_speed});
		}
	}

	void set_view()
	{
		if (is_editor_mode)
			set_view_editor();
		else
			set_view_player();
	}
	void update_backgrounds()
	{
		backgrounds[1].setTextureRect(sf::IntRect(18 * time, 0, 1200, 900));
		backgrounds[0].setTextureRect(sf::IntRect(22 * time, 0, 1200, 900));
	}

	void update(float dt)
	{	
		time += dt;
		set_view();
		update_backgrounds();
		player.update(dt);
		player.handle_all_collisions({num_tiles_x, num_tiles_y}, {tilesize * scale_factor, tilesize * scale_factor}, tilegrid);
        skeleton.handle_all_collisions({num_tiles_x, num_tiles_y}, {tilesize * scale_factor, tilesize * scale_factor}, tilegrid);

		cout << player.get_position().x << " " << player.get_position().y << " " << skeleton.get_position().x << " " << skeleton.get_position().y << endl;
	}

	void draw_single_tile(sf::RenderWindow& window, Tile tile, sf::Vector2f position)
	{
		tile_sprite.setPosition(position);
		tile_sprite.setTextureRect(tile_texture_coords[tile]);
		window.draw(tile_sprite);
	}

	void draw(sf::RenderWindow& window)
	{
		set_window_view(window);
		for (int i = 0; i < 4; ++i)
        {
            window.draw(backgrounds[i]);
        }
        set_world_view(window);
		for (int i = 0; i < num_tiles_x; i++)
			for (int j = 0; j < num_tiles_y; j++)
			{
				sf::Vector2f current_position = {tilesize * scale_factor * i, tilesize * scale_factor * j};
				Tile current_tile = tilegrid[i + j * num_tiles_x];
				Tile current_decoration_tile = decoration_tilegrid[i + j * num_tiles_x];
				if ((int)current_decoration_tile >= (int)Tile::CaveCenter)
				{
					draw_single_tile(window, current_decoration_tile, current_position);
					draw_single_tile(window, current_tile, current_position);
				}
				else
				{
					draw_single_tile(window, current_tile, current_position);
					draw_single_tile(window, current_decoration_tile, current_position);
				}
			}
		
		player.draw(window);
			skeleton.draw(window);
	}

	void handle_events(const sf::RenderWindow& window, const sf::Event& event)
	{
		player.handle_events(event);
	}


	void save_to_file(std::string filename)
	{
		std::ofstream savefile;
		savefile.open(filename);
		savefile << num_tiles_x << " " << num_tiles_y << std::endl;
		
		for (int j = 0; j < num_tiles_y; j++)
		{
			for (int i = 0; i < num_tiles_x; i++)
			{
				savefile.width(2);
				savefile << (int)tilegrid[i + num_tiles_x * j] << " ";
			}
			savefile << std::endl;
		}

		for (int j = 0; j < num_tiles_y; j++)
		{
			for (int i = 0; i < num_tiles_x; i++)
			{
				savefile.width(2);
				savefile << (int)decoration_tilegrid[i + num_tiles_x * j] << " ";
			}
			savefile << std::endl;
		}

		savefile << "Player " << player.get_position().x << " " << player.get_position().y << std::endl;
		savefile.close();

	}

	void load_from_file(std::string filename)
	{
		std::ifstream loadfile;
		loadfile.open(filename);
		loadfile >> num_tiles_x >> num_tiles_y;
		tilegrid.resize(num_tiles_x * num_tiles_y);
		for (int j = 0; j < num_tiles_y; j++)
		{
			for (int i = 0; i < num_tiles_x; i++)
			{
				int temp;
				loadfile >> temp;
				tilegrid[i + num_tiles_x * j] = (Tile)temp;
			}
		}
		decoration_tilegrid.resize(num_tiles_x * num_tiles_y);
		for (int j = 0; j < num_tiles_y; j++)
		{
			for (int i = 0; i < num_tiles_x; i++)
			{
				int temp;
				loadfile >> temp;
				decoration_tilegrid[i + num_tiles_x * j] = (Tile)temp;
			}
		}
		std::string temp_name;
		loadfile >> temp_name;
		sf::Vector2f temp_position;
		loadfile >> temp_position.x >> temp_position.y;
		player.set_position(temp_position);
		loadfile.close();
	}
};