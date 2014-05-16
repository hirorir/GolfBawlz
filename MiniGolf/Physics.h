#ifndef PHYSICSOBJECTS_H
#define PHYSICSOBJECTS_H

#include <vector>
#include <list>
#include <gl\glew.h>
#include <glm\glm.hpp>

namespace physics{

	using namespace glm;
	using namespace std;

	static float timestep = 0.02f;						//physics timestep
	static vec3 gravity = vec3(0, -0.01f, 0);			//accel due to gravity

	enum PhysicsType : int{
	DEFAULT = 0,
	PLANE = 1,
	SPHERE = 2,
	};

	class PhysicsObject;					//forward declaration for physicsObjects
	class Collision;						//forward declaration for collisions

	static list<PhysicsObject*> physicsObjects;	//physicsObject containing the list of all the physicsObjects in the game

	class PhysicsObject{
	public:
		PhysicsObject(vector<vec3> pts, vector< vector<int> > poly, float m){
			points = pts;
			polygons = poly;
			mass = m;
			velocity = vec3(0.0f);
			type = DEFAULT;
			physicsObjects.push_back(this);
			itor = --physicsObjects.end();
		}

		PhysicsObject(PhysicsType p, float m){
			type = p;
			mass = m;
			velocity = vec3(0.0f);
			physicsObjects.push_back(this);
			itor = --physicsObjects.end();
		}

		PhysicsObject(){
			mass = 1;
			drag = 0;
			velocity = vec3(0.0f);
			type = DEFAULT;
		}

		~PhysicsObject(){
			physicsObjects.erase(itor);
		}

		vec3 get_velocity();

		static vec3 update(vec3 position, vec3 velocity);	//update the physicsObject for the tick

		void applyForce(vec3 force);		//force in Newtons

	protected:
		PhysicsType type;

	private:
		list<PhysicsObject*>::iterator itor;
		vector<vec3> points;				//collision mesh vertices for default object
		vector< vector<int> > polygons;		//List of polygon indices of the collision mesh vertices
		float drag;							//UNUSED: passive fluid friction, or drag
		
		float mass;							//mass of the object
		vec3 velocity;						//velocity that the object is currently traveling at
	};

	static list<Collision*> collisions;		//collision list containing all the collisions for this tick

	class Collision{
		list<Collision*>::iterator itor;
		PhysicsObject &a;					//Second object involved in collision
		PhysicsObject &b;					//First object involved in collision
		static void generateCollisions();	//generate the collisions needed to be checked for this tick
		void resolveCollision();			//resolve this collision (use the update(float time) function)

		explicit Collision(PhysicsObject &a, PhysicsObject &b) : a(a), b(b){
			collisions.push_back(this);
			itor = --collisions.end();
		}

		~Collision(){
			collisions.erase(itor);
		}
	};
}

#endif