#include "Menu.h"
#include <assert.h>

namespace ArkanoidGame
{
	void Menu::Init(const MenuItem& item)
	{
		rootItem = item;

		InitMenuItem(rootItem);
		if (!rootItem.children.empty())
		{
			SelectMenuItem(rootItem.children.front());
		}
	}

	void Menu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.children)
		{
			child.parent = &item;
			InitMenuItem(child);
		}
	}

	void Menu::SelectMenuItem(MenuItem& item)
	{
		// It is definitely error to select root item
		assert(&item != &rootItem);

		if (selectedItem == &item)
		{
			return;
		}

		if (!item.isEnabled)
		{
			// Don't allow to select disabled item
			return;
		}

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->deselectedColor);
		}

		selectedItem = &item;

		if (selectedItem)
		{
			selectedItem->text.setFillColor(selectedItem->selectedColor);
		}
	}

	void Menu::SwitchToPreviousMenuItem()
	{
		// No item selected  Exit
		if (!selectedItem)
		{
			return;
		}
		// Get parent(submenu)
		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		// Search for the currently selected item in the list of children of the parent
		auto it = std::find_if(parent->children.begin(), parent->children.end(), [this](const auto& item) {
			return selectedItem == &item;	// compare by address
			});
		// Unless we are at the very first point
		if (it != parent->children.begin())
		{
			SelectMenuItem(*std::prev(it));	// Select the previous item
		}

	}

	void Menu::SwitchToNextMenuItem()
	{
		if (!selectedItem)
		{
			return;
		}
		
		MenuItem* parent = selectedItem->parent;
		assert(parent); // There always should be parent

		auto it = std::find_if(parent->children.begin(), parent->children.end(), [this](const auto& item) {
			return selectedItem == &item;
			});
		it = std::next(it);
		if (it != parent->children.end())
		{
			SelectMenuItem(*it);
		}
	}

	void Menu::PressOnSelectedItem()
	{
		if (!selectedItem)
		{
			return;
		}

		if (selectedItem->onPressCallBack)
		{
			selectedItem->onPressCallBack(*selectedItem);
			return;
		}

		// default behaviour
		if (!selectedItem->children.empty())
		{
			SelectMenuItem(selectedItem->children.front());
		}
	}

	void Menu::GoBack()
	{
		MenuItem& parent = GetCurrentContext();
		if (&parent != &rootItem)
		{
			SelectMenuItem(parent);
		}
	}

	MenuItem& Menu::GetCurrentContext()
	{
		return selectedItem ? *(selectedItem->parent) : rootItem;
	}

	void Menu::Draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem& expandedItem = GetCurrentContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem.children.size());
		for (auto& child : expandedItem.children)
		{
			if (child.isEnabled)
			{
				texts.push_back(&child.text);
			}
		}

		DrawTextList(
			window, 
			texts, 
			expandedItem.childrenSpacing, 
			expandedItem.childrenOrientation, 
			expandedItem.childrenAlignment, 
			position, 
			origin);
	}

}
