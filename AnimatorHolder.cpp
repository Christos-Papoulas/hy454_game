#include "header_files\animator\AnimatorHolder.h"

std::vector<Animator*> AnimatorHolder::running, AnimatorHolder::suspended;

void AnimatorHolder::Progress(timestamp_t currTime) {
		for (Dim i=0; i<running.size(); ++i)
				running[i]->Progress(currTime);
}

void AnimatorHolder::Display(Bitmap at) {
		for (Dim i=0; i<running.size(); ++i)
				running[i]->Display(at);
}

void AnimatorHolder::Register(Animator* a) { 
		suspended.push_back(a); 
}

void AnimatorHolder::Cancel(Animator* a) { 
		assert(a);
		std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
		assert( it != suspended.end() ); 
		suspended.erase(it);
}

void AnimatorHolder::MarkAsRunning(Animator* a) { 
		std::vector<Animator*>::iterator it = std::find(suspended.begin(), suspended.end(), a);
		if( it == suspended.end() ) return ; 
		suspended.erase(it); 
		running.push_back(a); 
}

void AnimatorHolder::MarkAsSuspended (Animator* a) { 
		std::vector<Animator*>::iterator it = std::find(running.begin(), running.end(), a);
		if( it == running.end() ) return ; 
		running.erase(it); 
		suspended.push_back(a);  
}
