#include "cauldron-common/primitives.h"
#pragma once
namespace cauldron::ecs {
	class entity_t;
	class tag_t;
	class filter_t;
	class cache_t;

	class scene {
	public:
		scene()						= default;
		~scene()					= default;

		scene(scene&)				= delete;
		scene(scene&&)				= delete;
		scene& operator=(scene&)	= delete;
		scene& operator=(scene&&)	= delete;

		// Registers a component type
		// Creates a buffer for it with 'page_size' instances per page
		template<class T>
		void registerComponent(u64 page_size);

		// Adds a component of type T to given entity
		template<class T>
		T* addComponent(entity_t* owner);
		// Removes a index-th component of type T from given entity
		template<class T>
		void removeComponent(entity_t* owner, u64 index = 0);
		// Returns a pointer to index-th component of type T owned by given entity
		template<class T>
		T* getComponent(entity_t* owner, u64 index = 0);

		// Sets entity tag
		void setTag(entity_t* entity, tag_t* tag);
		// Clears entity tag
		void clearTag(entity_t* entity, tag_t* tag);
		// Returns true if entity is tagged with given tag
		bool isTagged(entity_t* entity, tag_t* tag);

		// Caches a cache of entities that match filter
		cache_t* createCache(filter_t* filter);
		// Destroys the cache(but not the entities within them)
		void destroyCache(cache_t* group);

	private:
	};
}