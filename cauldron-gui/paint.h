#include "cauldron-common/primitives.h"
#include "cauldron-common/bounds.h"
#include "cauldron-common/color.h"
#include "cauldron-common/macro.coreManip.h"
#include "cauldron-common/macro.autoOperator.h"
#undef near;
#undef far;
#pragma once
namespace cauldron::gui {
	class control;
	
	class paint {
	public:
		class core_t;

		using bounds_t	= common::bounds2<f32>;
		using vector_t	= common::vector2<f32>;
		using color_t	= common::rgba8;

		enum class alignment : u32 {
			near	= 0,
			center	= 1,
			far		= 2
		};
		class font final {
		public:
			enum class style : u32 {
				normal		= 0x00,
				bold		= (1u << 0u),
				italic		= (1u << 1u),
				strikeout	= (1u << 2u),
				underline	= (1u << 3u),
			};
			class core_t;

			font();
			font(cwstr family, f32 size, style style = style::normal);
			~font();

			bool isValid() const;
			f32 getSize() const;
			style getStyle() const;

			//static font make(cwstr family, f32 size, style style = style::normal);
			
			INLINE_CORE_GET(core_t, _core);
			INLINE_CORE_MOVE(font, core_t, _core);
			INLINE_CORE_SWAP(font, core_t, _core);

		private:
			font(core_t*);
			core_t* _core;
		};
		
		class image {
		public:
			class core_t;

			image(cwstr path);
			~image();
			image(const image& copy) = delete;
			image& operator=(const image& copy) = delete;
			image& operator=(image&& move) = delete;
			image(image&& move) noexcept;
			void swap(image&& swap) noexcept;

			u64 getWidth() const;
			u64 getHeight() const;

			INLINE_CORE_GET(core_t, _core);
			
		protected:
			image(core_t* core);
			INLINE_CORE_SET(core_t, _core);

		private:
			core_t* _core;
		};
		class bitmap : public image {
		public:
			bitmap(cwstr path);
			bitmap(u64 width, u64 height);

			bitmap(const bitmap& move) = delete;
			bitmap& operator=(const bitmap& move) = delete;
			bitmap(bitmap&& move) noexcept;
			bitmap& operator=(bitmap&& move) = delete;
			void swap(bitmap&& swap) noexcept;

			~bitmap() = default;

		};
		class brush {
		public:
			class core_t;

			INLINE_CORE_GET(core_t, _core);

			~brush();

		protected:
			brush(core_t* core);

		private:
			core_t* _core;
		};
		class solidBrush : public brush {
		public:
			solidBrush(common::rgba8 color);
			~solidBrush() = default;

			common::rgba8 getColor() const;
			void setColor(common::rgba8 color);
		};
		class textureBrush : public brush {
		public:
			textureBrush(const image& image, const common::bounds2<f32>& bounds);
			~textureBrush() = default;

		private:
		};
		class pen {
		public:
			class core_t;

			pen(const brush& brush, f32 width = 1.0f);
			~pen();

			INLINE_CORE_GET(core_t, _core);
			INLINE_CORE_MOVE(pen, core_t, _core);
			INLINE_CORE_SWAP(pen, core_t, _core);

			f32 getWidth() const;

			void setBrush(const brush& brush);
			void setWidth(f32 width);

		private:
			core_t* _core;
		};

		paint();
		paint(control& ctrl);
		paint(bitmap& bmp);
		paint(const paint&) = delete;
		paint& operator=(const paint&) = delete;
		~paint();

		void initialize(control& windo);
		void initialize(bitmap& bitma);
		void terminate();
		bool isInitialized() const;

		INLINE_CORE_GET(core_t, _core);
		INLINE_CORE_SWAP(paint, core_t, _core);

		void setSmoothing(bool smoothing);
		void clear(common::rgba8 color);
		void setTransform(
			f32 m11, f32 m12, 
			f32 m21, f32 m22, 
			f32 m31, f32 m32);
		void clearTransform();
		void setClip(const common::bounds2<f32>& clip);
		void clearClip();

		static bounds_t measureWrite(
			cwstr text, 
			i32 length,
			const bounds_t& bounds,
			const font& font,
			alignment horizontal = alignment::near,
			alignment vertical = alignment::near);
		i32 pointToCaretIndex(
			cwstr text,
			i32 length,
			const bounds_t& bounds,
			const font& font,
			alignment horizontal,
			alignment vertical,
			const vector_t& point);
		void write(
			cwstr text,
			i32 length,
			const bounds_t& bounds,
			const font& font, 
			const brush& brush,
			alignment horizontal = alignment::near,
			alignment vertical = alignment::near);

		void drawImage(
			const bounds_t& bounds,
			const image& image);

		void drawRect(
			const bounds_t& bounds,
			const pen& pen);
		void drawEllipse(
			const bounds_t& bounds,
			const pen& pen);
		void drawLine(
			const vector_t& from,
			const vector_t& to,
			const pen& pen);
		void drawArc(
			const bounds_t& bounds,
			const vector_t angleSweep,
			const pen& pen);
		void drawPoly(
			const vector_t* points,
			u64 count,
			const pen& pen);
		void drawCurve(
			const vector_t* points,
			u64 count,
			const pen& pen);
		void drawBezier(
			const vector_t& from,
			const vector_t& control1,
			const vector_t& control2,
			const vector_t& to,
			const pen& pen);

		void fillRect(
			const bounds_t& bounds,
			const brush& brush);
		void fillEllipse(
			const bounds_t& bounds,
			const brush& brush);
		void fillArc(
			const bounds_t& bounds,
			const vector_t angleSweep,
			const brush& brush);
		void fillPoly(
			const vector_t* points,
			u64 count,
			const brush& brush);

	private:
		paint(core_t* core);
		core_t* _core;

	};
	INLINE_BITWISE_AND(paint::font::style);
	INLINE_BITWISE_OR(paint::font::style);
	INLINE_BITWISE_XOR(paint::font::style);
	INLINE_BITWISE_INVERT(paint::font::style);
}