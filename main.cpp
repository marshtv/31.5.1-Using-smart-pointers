#include <iostream>
#include <string>
#include <memory>

class Toy {
	private:
	std::string name;
	public:
	Toy(std::string _name) {
		this->name.resize(_name.size());
		this->name = _name;
	}
	Toy() = default;
	Toy(const Toy& other) {
		this->name.resize(other.name.size());
		this->name = other.name;
	}
	Toy& operator=(const Toy& other) {
		if (this == &other)
			return *this;
		this->name.resize(other.name.size());
		this->name = other.name;
		return *this;
	}

	std::string get_name() {
		return this->name;
	}
};

class Dog {
	private:
	std::string name;
	std::shared_ptr<Toy>  dog_toy;
	public:
	Dog(std::string _name) {
		this->name.resize(_name.size());
		this->name = _name;
	}

	Dog() = default;

	Dog(const Dog& other) {
		this->name.resize(other.name.size());
		this->name = other.name;
		if (other.dog_toy != nullptr)
			dog_toy = other.dog_toy;
	}

	Dog& operator=(const Dog& other) {
		if (this == &other)
			return *this;
		this->name.resize(other.name.size());
		this->name = other.name;
		if (other.dog_toy != nullptr)
			dog_toy = other.dog_toy;
		return *this;
	}

	~Dog() {
		drop_toy();
		std::cout << this->name << " is dead." << std::endl;
	};

	void get_up_toy(const std::shared_ptr<Toy>& _new_toy_ptr) {
		if (this->dog_toy == _new_toy_ptr)
			std::cout << this->name << " already have this toy" << std::endl;
		else {
			if (dog_toy != nullptr) this->drop_toy();
			dog_toy = _new_toy_ptr;
			std::cout << this->name << " pick up toy " << dog_toy->get_name() << "." << std::endl;
		}
	}

	void drop_toy() {
		if (dog_toy != nullptr) {
			std::cout << this->name << " dropped toy " << dog_toy->get_name() << "." << std::endl;
			dog_toy = nullptr;
		}
	}

	std::string get_name() {
		return this->name;
	}

	std::shared_ptr<Toy> get_toy() {
			return this->dog_toy;
	}
};

void show_ptr_count(const std::shared_ptr<Toy>& _shrd_ptr) {
	std::cout << _shrd_ptr->get_name() << " owned by " << _shrd_ptr.use_count() - 1 << " dogs." << std::endl;
}

int main() {
	std::shared_ptr<Toy> ball = std::make_shared<Toy>("Ball");
	std::shared_ptr<Toy> bone = std::make_shared<Toy>("Bone");
	show_ptr_count(ball);
	show_ptr_count(bone);
	std::cout << "-----------------------" << std::endl;

	Dog* sharik = new Dog("Sharik");
	Dog* tuzik = new Dog("Tuzik");
	std::cout << "-----------------------" << std::endl;

	sharik->get_up_toy(ball);
	show_ptr_count(ball);
	std::cout << "-----------------------" << std::endl;
	tuzik->get_up_toy(bone);
	show_ptr_count(bone);
	std::cout << "-----------------------" << std::endl;

	std::cout << sharik->get_name() << " have toy -> " << sharik->get_toy()->get_name() << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << tuzik->get_name() << " have toy -> " << tuzik->get_toy()->get_name() << std::endl;
	std::cout << "-----------------------" << std::endl;

	sharik->get_up_toy(bone);
	tuzik->get_up_toy(ball);
	show_ptr_count(ball);
	show_ptr_count(bone);
	std::cout << "-----------------------" << std::endl;

	std::cout << sharik->get_name() << " have toy -> " << sharik->get_toy()->get_name() << std::endl;
	std::cout << "-----------------------" << std::endl;
	std::cout << tuzik->get_name() << " have toy -> " << tuzik->get_toy()->get_name() << std::endl;
	std::cout << "-----------------------" << std::endl;
	delete sharik;
	std::cout << "-----------------------" << std::endl;
	delete tuzik;
	std::cout << "-----------------------" << std::endl;
	show_ptr_count(ball);
}
