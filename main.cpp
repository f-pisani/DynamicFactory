#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "DynamicFactory.hpp"

class AbstractComponent
{
	public:
		AbstractComponent() : id_(next_id_++)
		{
		}

		virtual ~AbstractComponent()
		{
		}

		virtual void DisplayInfo() const
		{
			std::cout << "Abstract Component [ID: " << id_ << "]" << std::endl;
		}

		virtual void Update(float deltaTime) = 0;
		virtual std::string GetType() const = 0;

		int GetId() const { return id_; }

	protected:
		int id_;
		static int next_id_;
};

int AbstractComponent::next_id_ = 1;

class HealthComponent : public AbstractComponent
{
	private:
		float health_;
		float maxHealth_;

	public:
		HealthComponent() : health_(100.0f), maxHealth_(100.0f)
		{
			std::cout << "HealthComponent created [ID: " << id_ << "]" << std::endl;
		}

		~HealthComponent()
		{
			std::cout << "HealthComponent destroyed [ID: " << id_ << "]" << std::endl;
		}

		void DisplayInfo() const override
		{
			std::cout << "Health Component [ID: " << id_ << "] - HP: " 
			          << health_ << "/" << maxHealth_ << std::endl;
		}

		void Update(float deltaTime) override
		{
			health_ = std::min(health_ + deltaTime * 5.0f, maxHealth_);
		}

		std::string GetType() const override { return "HealthComponent"; }

		void TakeDamage(float damage) 
		{ 
			health_ = std::max(0.0f, health_ - damage);
		}
};

class WeaponComponent : public AbstractComponent
{
	private:
		std::string weaponName_;
		float damage_;
		float fireRate_;

	public:
		WeaponComponent() : weaponName_("Plasma Rifle"), damage_(25.0f), fireRate_(2.0f)
		{
			std::cout << "WeaponComponent created [ID: " << id_ << "]" << std::endl;
		}

		~WeaponComponent()
		{
			std::cout << "WeaponComponent destroyed [ID: " << id_ << "]" << std::endl;
		}

		void DisplayInfo() const override
		{
			std::cout << "Weapon Component [ID: " << id_ << "] - " 
			          << weaponName_ << " (Damage: " << damage_ 
			          << ", Fire Rate: " << fireRate_ << ")" << std::endl;
		}

		void Update(float deltaTime) override
		{
			(void)deltaTime;
		}

		std::string GetType() const override { return "WeaponComponent"; }
};

class ShieldComponent : public AbstractComponent
{
	private:
		float shieldStrength_;
		float rechargeRate_;
		bool active_;

	public:
		ShieldComponent() : shieldStrength_(50.0f), rechargeRate_(10.0f), active_(true)
		{
			std::cout << "ShieldComponent created [ID: " << id_ << "]" << std::endl;
		}

		~ShieldComponent()
		{
			std::cout << "ShieldComponent destroyed [ID: " << id_ << "]" << std::endl;
		}

		void DisplayInfo() const override
		{
			std::cout << "Shield Component [ID: " << id_ << "] - Strength: " 
			          << shieldStrength_ << " (Active: " 
			          << (active_ ? "Yes" : "No") << ")" << std::endl;
		}

		void Update(float deltaTime) override
		{
			if (active_ && shieldStrength_ < 50.0f)
			{
				shieldStrength_ = std::min(50.0f, shieldStrength_ + rechargeRate_ * deltaTime);
			}
		}

		std::string GetType() const override { return "ShieldComponent"; }
};

void PrintSeparator()
{
	std::cout << "----------------------------------------" << std::endl;
}

void DemonstrateBasicUsage(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Basic Factory Usage ===" << std::endl;
	PrintSeparator();

	std::cout << "Creating components using factory:" << std::endl;
	auto* health = factory.CreateInstance("HealthComponent");
	auto* weapon = factory.CreateInstance("WeaponComponent");
	auto* shield = factory.CreateInstance("ShieldComponent");

	std::cout << "\nComponent information:" << std::endl;
	if (health) health->DisplayInfo();
	if (weapon) weapon->DisplayInfo();
	if (shield) shield->DisplayInfo();

	delete health;
	delete weapon;
	delete shield;
}

void DemonstrateErrorHandling(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Error Handling ===" << std::endl;
	PrintSeparator();

	std::cout << "Attempting to create non-existent component type:" << std::endl;
	auto* invalid = factory.CreateInstance("NonExistentComponent");
	
	if (invalid == nullptr)
	{
		std::cout << "✓ Factory correctly returned nullptr for invalid type" << std::endl;
	}
	else
	{
		std::cout << "✗ Factory should have returned nullptr!" << std::endl;
		delete invalid;
	}
}

void DemonstrateClassChecking(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Class Registration Checking ===" << std::endl;
	PrintSeparator();

	std::vector<std::string> classNames = {
		"HealthComponent", 
		"WeaponComponent", 
		"ShieldComponent",
		"InventoryComponent",
		"AIComponent"
	};

	std::cout << "Checking registered classes:" << std::endl;
	for (const auto& className : classNames)
	{
		bool isRegistered = factory.isClass(className);
		std::cout << std::setw(20) << std::left << className 
		          << " : " << (isRegistered ? "✓ Registered" : "✗ Not Registered") 
		          << std::endl;
	}
}

void DemonstrateUnregistration(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Dynamic Registration/Unregistration ===" << std::endl;
	PrintSeparator();

	std::cout << "Before unregistering WeaponComponent:" << std::endl;
	std::cout << "WeaponComponent registered: " 
	          << (factory.isClass("WeaponComponent") ? "Yes" : "No") << std::endl;

	factory.UnregisterClass("WeaponComponent");

	std::cout << "\nAfter unregistering WeaponComponent:" << std::endl;
	std::cout << "WeaponComponent registered: " 
	          << (factory.isClass("WeaponComponent") ? "Yes" : "No") << std::endl;

	auto* weapon = factory.CreateInstance("WeaponComponent");
	if (!weapon)
	{
		std::cout << "✓ Cannot create unregistered component" << std::endl;
	}

	std::cout << "\nRe-registering WeaponComponent..." << std::endl;
	factory.RegisterClass<WeaponComponent>("WeaponComponent");
	
	weapon = factory.CreateInstance("WeaponComponent");
	if (weapon)
	{
		std::cout << "✓ Successfully created re-registered component" << std::endl;
		weapon->DisplayInfo();
		delete weapon;
	}
}

void DemonstratePolymorphicUsage(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Polymorphic Usage with Entity System ===" << std::endl;
	PrintSeparator();

	std::vector<std::unique_ptr<AbstractComponent>> entity;
	
	std::cout << "Building entity from component list:" << std::endl;
	std::vector<std::string> componentList = {"HealthComponent", "WeaponComponent", "ShieldComponent"};
	
	for (const auto& componentType : componentList)
	{
		auto* component = factory.CreateInstance(componentType);
		if (component)
		{
			entity.push_back(std::unique_ptr<AbstractComponent>(component));
			std::cout << "Added " << componentType << " to entity" << std::endl;
		}
	}

	std::cout << "\nEntity components:" << std::endl;
	for (const auto& component : entity)
	{
		component->DisplayInfo();
	}

	std::cout << "\nSimulating entity update (0.1s):" << std::endl;
	for (auto& component : entity)
	{
		component->Update(0.1f);
	}

	std::cout << "\nEntity components after update:" << std::endl;
	for (const auto& component : entity)
	{
		component->DisplayInfo();
	}
}

void DemonstrateFactoryInfo(DynamicFactory<AbstractComponent>& factory)
{
	std::cout << "\n=== Factory Information ===" << std::endl;
	PrintSeparator();

	std::cout << "Factory hash code: " << factory.getDynamicFactoryHash() << std::endl;
	std::cout << "This hash is based on the base type (AbstractComponent)" << std::endl;
}

int main()
{
	std::cout << "==================================" << std::endl;
	std::cout << "    DynamicFactory Demo v1.0     " << std::endl;
	std::cout << "==================================" << std::endl;

	DynamicFactory<AbstractComponent> componentFactory;

	std::cout << "\nRegistering component types..." << std::endl;
	componentFactory.RegisterClass<HealthComponent>("HealthComponent");
	componentFactory.RegisterClass<WeaponComponent>("WeaponComponent");
	componentFactory.RegisterClass<ShieldComponent>("ShieldComponent");
	std::cout << "✓ Registration complete" << std::endl;

	DemonstrateBasicUsage(componentFactory);
	DemonstrateErrorHandling(componentFactory);
	DemonstrateClassChecking(componentFactory);
	DemonstrateUnregistration(componentFactory);
	DemonstratePolymorphicUsage(componentFactory);
	DemonstrateFactoryInfo(componentFactory);

	std::cout << "\n==================================" << std::endl;
	std::cout << "    Demo Complete                " << std::endl;
	std::cout << "==================================" << std::endl;

	return 0;
}
