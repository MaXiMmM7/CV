


#include "node.h"







	DateComparisonNode::DateComparisonNode(const Comparison& cmp,const Date& date):cmp(cmp),helper(date){}
	//<DateComparisonNode>(cmp, ParseDate(is));




	EventComparisonNode::EventComparisonNode(const Comparison& cmp,const string& event):cmp(cmp),helper(event){}
	//<DateComparisonNode>(cmp, ParseDate(is));




	LogicalOperationNode::LogicalOperationNode(const LogicalOperation& logical_operation,shared_ptr<Node> node_left,
			shared_ptr<Node> node_right):
				operation(logical_operation),left_(node_left),right_(node_right){}


