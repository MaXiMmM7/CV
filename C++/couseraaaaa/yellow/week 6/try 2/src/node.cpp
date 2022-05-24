
#include "node.h"


	DateComparisonNode::DateComparisonNode(const Comparison& cmp, const Date& d){
		date_=d;
		oper_=cmp;
	}
	EventComparisonNode::EventComparisonNode(const Comparison& cmp, const string& event){
		oper_=cmp;
		event_=event;
	}

	LogicalOperationNode::LogicalOperationNode(const LogicalOperation& op, const shared_ptr<Node> left,
			const shared_ptr<Node> right){
		oper_=op;
		left_=left;
		right_=right;
	}
