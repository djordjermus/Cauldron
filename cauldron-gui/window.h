#pragma once
#include "group.h"
#include "control.h"
namespace cauldron::gui {
	class window : public control, public group {
	public:
		enum class state : u32 {
			hidden		= 0x00,
			normal		= 0x01,
			minimized	= 0x02,
			maximized	= 0x03,
		};
		enum class style : u32 {
			none			= 0x00,
			bordered		= (1ull << 0ull),
			captioned		= (1ull << 1ull),
			resizable		= (1ull << 2ull),
			minimize_button	= (1ull << 3ull),
			maximize_button	= (1ull << 4ull)
		};
		class changeParentData : public common::eventData {
		public:
			changeParentData(control* child, control* old_parent, control* new_parent);
	
			control* getChild() const;
			control* getOldParent() const;
			control* getNewParent() const;
	
		private:
			control* _child;
			control* _old_parent;
			control* _new_parent;
		};

		window();

		f32 getOpacity() const;

		virtual bool setState(state state);
		virtual bool setStyle(style style);
		virtual bool setOpacity(f32 opacity);

	private:
		std::vector<control*> _children =
			std::vector<control*>();
		f32 _opacity = 
			1.0f;
	};
	
	INLINE_BITWISE_OR(window::style);
	INLINE_BITWISE_AND(window::style);
	INLINE_BITWISE_XOR(window::style);
}
