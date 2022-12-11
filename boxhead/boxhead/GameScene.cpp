#include "pch.hpp"
#include "GameScene.hpp"
#include "Framework.hpp"

void MapManager::Awake(Scene* scene)
{
	// �� �ѹ��� ���� �� ����
	for (size_t i = 0; i < boardSizeW; i++)
	{
		for (size_t j = 0; j < boardSizeH; j++)
		{
			// �� �켱���� ����
			auto& terrain_cell = GetTerrainAt(i, j);

			if (terrain_cell == 1 || terrain_cell == 2)
			{
				float cell_height = 1.0f;
				heightMap.emplace_back(i, j, cell_height);
			}
		}
	}

	// �� ��������
	auto wall_model_view = ModelView::GetReference<SideCubeModel>();

	// ���� ���� ������ �� ����
	for (auto& height_block : heightMap)
	{
		const float cx = boardScaleW * static_cast<float>(height_block.x);
		const float cz = boardScaleH * static_cast<float>(height_block.y);

		Entity* wall = scene->CreateEntity<Entity>(wall_model_view, cx, 0.5f, cz);
	}
}

void MapManager::Start(Scene* scene)
{}
