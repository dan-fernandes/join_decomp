#include "XCSP3CoreParser.h"
#include "JoinDecomp.h"
#include "JoinDecompBuilder.h"
//#include "XCSP3JoinDecompCallbacks.h"


using namespace XCSP3Core;

int main(int argc,char **argv) {
    // XCSP3JoinDecompCallbacks cb; // my interface between the parser and the solver

   if(argc!=2)
     throw std::runtime_error("usage: ./test xcsp3instance.xml");
  try
  {
    // XCSP3CoreParser parser(&cb);
    // parser.parse(argv[1]); // fileName is a string
    JoinDecompBuilder jdb;
    JoinDecomp * jd;

    jdb.loadXCSP(argv[1]);
    jd = jdb.buildJoinDecomp();

    jd->solve();
    int width = jd->joinwidth();

    return width;

  }
  catch (exception &e)
  {
    cout.flush();
    cerr << "\n\tUnexpected exception :\n";
    cerr << "\t" << e.what() << endl;
    exit(1);
  }

  return 0;
}
