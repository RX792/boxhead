#include "pch.hpp"
#include "GameScene.hpp"
#include "Framework.hpp"

void MapManager::Awake(Scene* scene)
{
	// 딱 한번만 높이 맵 생성
	for (size_t i = 0; i < boardSizeW; i++)
	{
		for (size_t j = 0; j < boardSizeH; j++)
		{
			// 열 우선으로 삽입
			auto& terrain_cell = GetTerrainAt(i, j);

			if (terrain_cell == 1 || terrain_cell == 2)
			{
				float cell_height = 1.0f;
				heightMap.emplace_back(i, j, cell_height);
			}
		}
	}

	// 모델 가져오기
	auto wall_model_view = ModelView::GetReference<SideCubeModel>();

	// 높이 맵의 내용대로 벽 생성
	for (auto& height_block : heightMap)
	{
		const float cx = boardScaleW * static_cast<float>(height_block.x);
		const float cz = boardScaleH * static_cast<float>(height_block.y);

		Entity* wall = scene->CreateEntity<Entity>(wall_model_view, cx, 0.5f, cz);
	}
}

void MapManager::Start(Scene* scene)
{}
