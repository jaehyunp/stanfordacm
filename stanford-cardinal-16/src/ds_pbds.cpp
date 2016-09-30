typedef tree<int, null_type, less<int>,
	rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set X;
X.insert(1);
cout << *X.find_by_order(0) << endl;
cout << X.order_of_key(1) << endl;