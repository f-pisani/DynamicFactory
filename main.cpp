#include <iostream>

#include "DynamicFactory.hpp"

class AbstractComponent
{
	public:
		AbstractComponent()
		{
		}

		virtual ~AbstractComponent()
		{
		}

		virtual void DisplayInfo()
		{
			std::cout << "Abstract Component" << std::endl;
		}
};

class HealthComponent : public AbstractComponent
{
	public:
		HealthComponent()
		{
		}

		~HealthComponent()
		{
		}

		void DisplayInfo()
		{
			std::cout << "HP Component" <<  std::endl;
		}
};

class WeaponComponent : public AbstractComponent
{
	public:
		WeaponComponent()
		{
		}

		~WeaponComponent()
		{
		}

		void DisplayInfo()
		{
			std::cout << "Weapon Component" <<  std::endl;
		}
};

int main()
{
	DynamicFactory<AbstractComponent> componentFactory;
		componentFactory.RegisterClass<HealthComponent>("HealthComponent");
		componentFactory.RegisterClass<WeaponComponent>("WeaponComponent");

	AbstractComponent* hp_component = componentFactory.CreateInstance("HealthComponent");
	AbstractComponent* weapon_component = componentFactory.CreateInstance("WeaponComponent");

	hp_component->DisplayInfo();
	weapon_component->DisplayInfo();

    return 0;
}
