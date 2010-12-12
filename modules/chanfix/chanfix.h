/* chanfix - channel fixing service
 * Copyright (c) 2010 Atheme Development Group
 */

#ifndef __CHANFIX_H__
#define __CHANFIX_H__

#define CHANFIX_RETENTION_TIME		(86400 * 14)

typedef struct chanfix_channel {
	char *name;

	mowgli_list_t oprecords;
	time_t ts;
	time_t lastupdate;

	channel_t *chan;
} chanfix_channel_t;

typedef struct chanfix_oprecord {
	mowgli_node_t node;

	chanfix_channel_t *chan;

	myentity_t *entity;

	char user[USERLEN];
	char host[HOSTLEN];

	time_t firstseen;
	time_t lastevent;
	unsigned int age;
} chanfix_oprecord_t;

typedef struct chanfix_persist {
	int version;

	mowgli_heap_t *chanfix_channel_heap;
	mowgli_heap_t *chanfix_oprecord_heap;

	mowgli_patricia_t *chanfix_channels;
} chanfix_persist_record_t;

E service_t *chanfix;
E mowgli_patricia_t *chanfix_channels;

E void chanfix_gather_init(chanfix_persist_record_t *);
E void chanfix_gather_deinit(module_unload_intent_t, chanfix_persist_record_t *);

E void chanfix_oprecord_update(chanfix_channel_t *chan, user_t *u);
E void chanfix_oprecord_delete(chanfix_oprecord_t *orec);
E chanfix_oprecord_t *chanfix_oprecord_create(chanfix_channel_t *chan, user_t *u);
E chanfix_oprecord_t *chanfix_oprecord_find(chanfix_channel_t *chan, user_t *u);
E chanfix_channel_t *chanfix_channel_create(const char *name, channel_t *chan);
E chanfix_channel_t *chanfix_channel_find(const char *name);
E chanfix_channel_t *chanfix_channel_get(channel_t *chan);
E void chanfix_channel_delete(chanfix_channel_t *c);

E void chanfix_autofix_ev(void *unused);

E command_t cmd_chanfix;
E command_t cmd_scores;

#endif
