#ifndef ITEXT_EDITOR_LISTENER_H
#define ITEXT_EDITOR_LISTENER_H

namespace obaro
{
	namespace editor
	{
		template<class TDerive>
		class ITextEditorListener
		{
		public:
			ITextEditorListener();

		};
	}
}

using namespace obaro::editor;

template<class TDerive>
ITextEditorListener<TDerive>::ITextEditorListener()
{

}


//Now implementations here
#endif