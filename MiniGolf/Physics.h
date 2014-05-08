#ifndef PHYSICSOBJECTS_H
#define PHYSICSOBJECTS_H

#include <vector>
#include <gl\glew.h>
#include <glm\glm.hpp>

namespace physics{

	using namespace glm;
	using namespace std;

	static float timestep;
	static float gravity;

	enum PhysicsType : int{
	DEFAULT = 0,
	PLANE = 1,
	SPHERE = 2,
	};

	class PhysicsObject{
	public:
		static vector<PhysicsObject*> physObjects;
	private:
		vec3 position;
		vector<vec3> points;
		vector< vector<int> > polygons;
		float drag;

		float mass;
		vec3 velocity;

		PhysicsObject(vector<vec3> pts, vector< vector<int> > poly, float m){
			points = pts;
			polygons = poly;
			mass = m;
			//physObjects.insert(this);
		}

		PhysicsObject(){
			mass = 0;
			drag = 0;
			position = vec3(0.0f);
		}

		~PhysicsObject(){

		}

		void applyForce(vec3 force);		//force in Newtons
		void update();
	};

	class Collision{
		static vector<Collision> collisions;
		static void generateCollisions();
		void resolveCollision();
	};
}

#endif