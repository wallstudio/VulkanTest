#pragma once

#include <iostream>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_win32.h>
#pragma comment(lib, "vulkan-1.lib")

void Test()
{
    const auto layers = std::vector{ "VK_LAYER_KHRONOS_validation" };
    uint32_t extentionsCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionsCount, nullptr);
    auto extentions = std::vector<VkExtensionProperties>(extentionsCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionsCount, extentions.data());
    auto extentionNames = std::vector<const char*>();
    for (auto& extention : extentions)
    {
        extentionNames.push_back(extention.extensionName);
    }

    VkApplicationInfo applicationInfo =
    {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "App",
        .pEngineName = "App",
        .engineVersion = VK_MAKE_VERSION(0, 0, 0),
        .apiVersion = VK_API_VERSION_1_1,
    };
    VkInstanceCreateInfo instanceCreateInfo =
    {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &applicationInfo,
        .enabledLayerCount = (uint32_t)layers.size(),
        .ppEnabledLayerNames = layers.data(),
        .enabledExtensionCount = (uint32_t)extentionNames.size(),
        .ppEnabledExtensionNames = extentionNames.data(),
    };
    VkInstance instance;
    vkCreateInstance(&instanceCreateInfo, nullptr, &instance);

    uint32_t physicalDeviceCount;
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, nullptr);
    auto physicalDevices = std::vector<VkPhysicalDevice>(physicalDeviceCount);
    vkEnumeratePhysicalDevices(instance, &physicalDeviceCount, physicalDevices.data());

    VkPhysicalDeviceProperties physicalDeviceProps;
    vkGetPhysicalDeviceProperties(physicalDevices[0], &physicalDeviceProps);

    std::cout << physicalDeviceProps.deviceName << std::endl;
}

int main()
{
    Test();
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
