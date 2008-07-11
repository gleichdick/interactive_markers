
#include <wx/app.h>

#include "ros/node.h"
#include "wx_topic_display/TopicDisplay.h"

#include "GenTestTopicDisplay.h"



class TestTopicDisplay : public GenTestTopicDisplay
{
  TopicDisplay* topicDisplay;
  TopicDisplay* topicDisplay2;

  ros::node* node;

public:
  TestTopicDisplay(wxWindow* parent) : GenTestTopicDisplay(parent), node(NULL)
  {
    int argc = 0;
    ros::init(argc, NULL);

    node = new ros::node("TestTopicDisplay");

    topicDisplay = new TopicDisplay(topicPanel,node);
    topicDisplay2 = new TopicDisplay(topicPanel2,node);
  }

  ~TestTopicDisplay()
  {
    if (node)
      delete node;
  }

  virtual void onClose( wxCloseEvent& event )
  {
    printf("Shutting down ros...\n");
    ros::fini();
    
    event.Skip();
  }

  virtual void printSelections( wxCommandEvent& event )
  {
    printf("Panel1: \n");

    std::vector<std::string> selections = topicDisplay->getSelectedTopics();

    for (std::vector<std::string>::iterator i = selections.begin(); i != selections.end(); i++)
    {
      printf("%s is selected\n", i->c_str());
    }
    printf("\n");

    printf("Panel2: \n");

    selections = topicDisplay2->getSelectedTopics();

    for (std::vector<std::string>::iterator i = selections.begin(); i != selections.end(); i++)
    {
      printf("%s is selected\n", i->c_str());
    }
    printf("\n");

    event.Skip();
  }
};

class TestApp : public wxApp
{
public:
  TestApp() {  };

  virtual ~TestApp() { };

  virtual bool OnInit()
  {
    TestTopicDisplay* t = new TestTopicDisplay( (wxWindow*)NULL );
    t->Show();
    SetTopWindow( t );
    return true;
  }
};

DECLARE_APP(TestApp);

IMPLEMENT_APP(TestApp);


