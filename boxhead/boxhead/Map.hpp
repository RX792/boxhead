#pragma once
#include "Scene.hpp"
#include "GameScene.hpp"
#include "Entity.hpp"
#include "Model.hpp"
#include "Wall.hpp"

class MapManager
{
private:
	using TerrainItem = int;

public:
	class Block
	{
	public:
		constexpr Block(size_t ix, size_t iy, const float& height = 1.0f)
			: x(ix), y(iy), myHeight(height)
		{}

		constexpr Block& operator=(const float& height)
		{
			myHeight = height;

			return *this;
		}

		explicit operator float() const
		{
			return myHeight;
		}

		size_t x, y;
		float myHeight;
	};

	constexpr MapManager()
		: heightMap()
		, test_model(nullptr)
	{
		heightMap.reserve(boardSizeW * boardSizeH + 1);
	}

	virtual ~MapManager()
	{}

	void Awake(Scene* scene)
	{
		for (size_t i = 0; i < boardSizeW; i++)
		{
			for (size_t j = 0; j < boardSizeH; j++)
			{
				// 열 우선으로 삽입
				auto& terrain_cell = GetTerrainAt(i, j);

				if (terrain_cell == 1 || terrain_cell == 2)
				{
					float cell_height = 1.0f;
					heightMap.emplace_back(j, i, cell_height);
				}
			}
		}

		test_model = new SideCubeModel{ 1 };

		for (auto& height_block : heightMap)
		{
			const float cx = boardScaleW * static_cast<float>(height_block.x);
			const float cz = boardScaleH * static_cast<float>(height_block.y);

			Entity* wall = scene->CreateEntity<Entity>(test_model, cx, 0.5f, cz);
		}
	}

	void Start(Scene* scene)
	{}

	constexpr Block& CellAt(const size_t& x, const size_t& y)
	{
		const auto pos = x * boardSizeH + y;

		return heightMap.at(pos);
	}

	constexpr const Block& CellAt(const size_t& x, const size_t& y) const
	{
		const auto pos = x * boardSizeH + y;

		return heightMap.at(pos);
	}

	constexpr TerrainItem& SetTerrainAt(const size_t& x, const size_t& y, const int& value)
	{
		auto& cell = GetTerrainAt(x, y);
		cell = value;

		return cell;
	}

	constexpr TerrainItem& GetTerrainAt(const size_t& x, const size_t& y)
	{
		return terrainMap.at(y).at(x);
	}

	constexpr const TerrainItem& GetTerrainAt(const size_t& x, const size_t& y) const
	{
		return terrainMap.at(y).at(x);
	}

	Model* test_model;

	static inline constexpr size_t boardSizeW = 40;
	static inline constexpr size_t boardSizeH = 40;

private:
	static inline constexpr float boardScaleW = 1.0f;
	static inline constexpr float boardScaleH = 1.0f;

	std::vector<Block> heightMap;

	using TerrainRow = std::array<int, boardSizeH>;
	using Terrain = std::array<TerrainRow, boardSizeW>;
	Terrain terrainMap =
	{
		TerrainRow
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,1,2,0,0,0,0,0,2,1,2,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,2,0,0,0,2,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,1},

		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
};