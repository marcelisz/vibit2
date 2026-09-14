#ifndef _NORMALPAGES_H
#define _NORMALPAGES_H

#include <list>
#include <mutex>

#include "debug.h"
#include "ttxpagestream.h"
#include "pagelist.h"

// list of normal pages

namespace vbit
{

class NormalPages
{
    public:
        /** Default constructor
         *  @param reverse When true, pages are broadcast in descending page number order
         */
        NormalPages(int mag, PageList *pageList, Debug *debug, bool reverse=false);
        /** Default destructor */
        virtual ~NormalPages();

        std::shared_ptr<TTXPageStream> NextPage();

        void addPage(std::shared_ptr<TTXPageStream> p);

    protected:

    private:
        int _mag;
        PageList* _pageList;
        Debug* _debug;
        bool _reverse;
        std::list<std::shared_ptr<TTXPageStream>> _NormalPagesList;
        std::list<std::shared_ptr<TTXPageStream>>::iterator _iter;
        std::shared_ptr<TTXPageStream> _page;
};

}

#endif // _NORMALPAGES_H
