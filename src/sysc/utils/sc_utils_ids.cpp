/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2006 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  sc_utils_ids.cpp -- Report ids for the utils code.

  Original Author: Martin Janssen, Synopsys, Inc., 2002-01-17

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

  Alex Riesen, Synopsys, Inc., 2003-02-02
  ported to SystemC 2.1 exception reporting.
    
 *****************************************************************************/


// $Log: sc_utils_ids.cpp,v $
// Revision 1.1.1.1  2006/12/15 20:31:39  acg
// SystemC 2.2
//
// Revision 1.6  2006/01/31 21:42:07  acg
//  Andy Goodrich: Added checks for SC_DEPRECATED_WARNINGS being defined as
//  DISABLED. If so, we turn off the /IEEE_Std_1666/deprecated message group.
//
// Revision 1.5  2006/01/24 21:59:59  acg
//  Andy Goodrich: removed sc_trace_ids.h since its only message has been
//  replaced by SC_ID_IEEE_1666_DEPRECATION_ message.
//
// Revision 1.4  2006/01/24 20:53:41  acg
// Andy Goodrich: added warnings indicating that use of integer ids in reports
// is deprecated. Added tracing/sc_trace_ids.h to message list.
//
// Revision 1.3  2006/01/13 18:53:11  acg
// Andy Goodrich: Added $Log command so that CVS comments are reproduced in
// the source.
//

#include <cstdlib>
#include <cstring>
using namespace std;

#include "sysc/utils/sc_report.h"


namespace sc_core {
#define SC_DEFINE_MESSAGE(id,unused,text) extern const char id[] = text;
#include "sysc/utils/sc_utils_ids.h"
#include "sysc/kernel/sc_kernel_ids.h"
#include "sysc/communication/sc_communication_ids.h"
#include "sysc/datatypes/bit/sc_bit_ids.h"
#include "sysc/datatypes/fx/sc_fx_ids.h"
#include "sysc/datatypes/int/sc_int_ids.h"
#undef SC_DEFINE_MESSAGE


static sc_msg_def texts[] = {
#define SC_DEFINE_MESSAGE(id,n,unused) \
    { (id), 0u, {0u}, 0u, {0u}, 0u, 0u, {0u}, 0, n },

#undef SC_UTILS_IDS_H
#include "sysc/utils/sc_utils_ids.h"

#undef SC_KERNEL_IDS_H
#include "sysc/kernel/sc_kernel_ids.h"

#undef SC_COMMUNICATION_IDS_H
#include "sysc/communication/sc_communication_ids.h"

#undef SC_BIT_IDS_H
#include "sysc/datatypes/bit/sc_bit_ids.h"

#undef SC_FX_IDS_H
#include "sysc/datatypes/fx/sc_fx_ids.h"

#undef SC_INT_IDS_H
#include "sysc/datatypes/int/sc_int_ids.h"

#undef SC_DEFINE_MESSAGE
};
static sc_report_handler::msg_def_items items = {
    texts, sizeof(texts)/sizeof(*texts), false, 0
};

static
int initialize()
{
    sc_report_handler::add_static_msg_types(&items);

    // PROCESS ANY ENVIRONMENTAL OVERRIDES:

    const char* deprecation_warn = std::getenv("SC_DEPRECATION_WARNINGS");
    if ( (deprecation_warn!=0) && !strcmp(deprecation_warn,"DISABLE") )
    {
        sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", 
            SC_DO_NOTHING);
    }
    return 42;
}

static int forty_two = initialize();

} // namespace sc_core

// Taf!
