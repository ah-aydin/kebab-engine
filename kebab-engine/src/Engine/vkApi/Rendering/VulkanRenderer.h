#pragma once

#ifdef GRAPHICS_API_VULKAN

#define VK_NO_PROTOTYPES

#include <Engine/vkApi/VKWindow.h>
#include "VulkanPipeline.h"
#include "VulkanSwapchain.h"
#include "Systems/BasicRenderSystem.h"

#include <vector>
#include <memory>
#include <cassert>

namespace kbb::vkApi
{
	class VulkanRenderer
	{
	public:
		VulkanRenderer(VKWindow& window, VulkanDevice& device);
		~VulkanRenderer();

		VulkanRenderer(const VulkanRenderer&) = delete;
		VulkanRenderer& operator=(const VulkanRenderer) = delete;

		VkRenderPass getSwapchainRenderPass() const { return m_vulkanSwapchain->getRenderPass(); }
		bool isFrameInProgress() const { return m_isFrameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const
		{
			assert(m_isFrameStarted && "Cannot get command buffer when frame not in progress");
			return m_commandBuffers[m_currentFrameIndex];
		}

		VkDeviceMemory getCurrentUniformBufferMemory() const
		{
			assert(m_isFrameStarted && "Cannot get uniform buffer memory when frame is not in progress");
			return m_uniformBuffersMemory[m_currentFrameIndex];
		}

		float getSwapchainAspectRatio()
		{
			return m_vulkanSwapchain->width() / (float)m_vulkanSwapchain->height();
		}

		int getFrameIndex() const
		{
			assert(m_isFrameStarted && "Cannot get frame index when frame not in progress");
			return m_currentFrameIndex;
		}

		const std::vector<VkBuffer>& getUniformBuffers() const { return m_uniformBuffers; }

		void beginFrame(
			VkCommandBuffer& out_CommandBuffer,
			VkDeviceMemory& out_UniformBufferMemory,
			int& out_CurrentImageIndex
		);
		void endFrame(VkCommandBuffer commandBuffer);
		void beginSwapchainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapchainRenderPass(VkCommandBuffer commandBuffer);

		void render2D(
			VkCommandBuffer commandBuffer,
			VkDeviceMemory uniformBufferMemory,
			int currentImageIndex,
			std::vector<VKGameObject2D>& gameObjects
		) {
			m_renderSystem2D->renderGameObjects2D(commandBuffer, gameObjects);
		}
		void render3D(
			VkCommandBuffer commandBuffer,
			VkDeviceMemory uniformBufferMemory,
			int currentImageIndex,
			std::vector<VKGameObject3D>& gameObjects
		) {
			m_renderSystem3D->renderGameObjects3D(commandBuffer, uniformBufferMemory, currentImageIndex, gameObjects);
		}

		void destroyRenderSystems()
		{
			delete m_renderSystem2D;
			delete m_renderSystem3D;
		}

	private:

		VKWindow& m_window;
		VulkanDevice& m_vulkanDevice;
		std::unique_ptr<VulkanSwapchain> m_vulkanSwapchain;

		void createCommandBuffers();
		void freeCommandBuffers();
		std::vector<VkCommandBuffer> m_commandBuffers;

		void createUniformBuffers();
		std::vector<VkBuffer> m_uniformBuffers;
		std::vector<VkDeviceMemory> m_uniformBuffersMemory;

		void recreateSwapchain();

		uint32_t m_currentImageIndex;
		int m_currentFrameIndex;
		bool m_isFrameStarted = false;

		// Render systems
		void createRenderSystems();
		BasicRenderSystem* m_renderSystem2D;
		BasicRenderSystem* m_renderSystem3D;
	};
}
#endif