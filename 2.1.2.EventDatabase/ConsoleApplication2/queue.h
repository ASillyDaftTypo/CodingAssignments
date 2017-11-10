#ifndef QUEUE_H
#define QUEUE_H


// Standard queue template

template <class Type>
class queue
{
private:
	Type *Contents;
	int QueueSize;
	int Front, Back;
public:
	queue(int queuesize = 10);
	~queue();
	bool Empty() const;
	bool Full() const;
	bool Remove(Type& FrontElement);
	bool Add(const Type& NewElement);
	//Below added to allow for further functionality
	int GetQueueLength();
	void SearchContents(Type List[]);
};
#endif
