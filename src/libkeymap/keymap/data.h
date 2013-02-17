#ifndef LK_DATA_H
#define LK_DATA_H

#include <linux/kd.h>
#include <linux/keyboard.h>
#include <keymap/findfile.h>

#ifdef KDSKBDIACRUC
typedef struct kbdiacruc accent_entry;
#else
typedef struct kbdiacr accent_entry;
#endif

typedef enum {
	LKFLAG_UNICODE_MODE  = (1 << 1),
	LKFLAG_CLEAR_COMPOSE = (1 << 2),
	LKFLAG_CLEAR_STRINGS = (1 << 3),
} lkflags;

/* LOG_QUIET  - quiet (all messages are disabled)
 * LOG_NORMAL - normal output
 * LOG_VERBOSE{1,2,..} - verbosity levels
 */
typedef enum {
	LOG_QUIET = 0,
	LOG_NORMAL,
	LOG_VERBOSE1,
	LOG_VERBOSE2,
	LOG_VERBOSE3,
	LOG_MAXVALUE
} lkverbosity;

#define MAX_INCLUDE_DEPTH 20

struct keymap {
	/* Parser flags */
	lkflags flags;

	/* What keymaps are we defining? */
	u_short defining[MAX_NR_KEYMAPS];
	int max_keymap;              /* from here on, defining[] is false */

	/* the kernel structures we want to set or print */
	u_short *key_map[MAX_NR_KEYMAPS];
	char *func_table[MAX_NR_FUNC];

	accent_entry accent_table[MAX_DIACR];
	unsigned int accent_table_size;    

	char key_is_constant[NR_KEYS];
	char *keymap_was_set[MAX_NR_KEYMAPS];

	char keymaps_line_seen;      /* Keyword: "keymaps" */
	int alt_is_meta;             /* Keyword: "alt-is-meta" */
	int mod;                     /* Line by line modifiers */
	int key_buf[MAX_NR_KEYMAPS]; /* Key definitions on one line */

	int prefer_unicode;    

	int rvalct;
	int state_ptr;
	lkfile_t *stack[MAX_INCLUDE_DEPTH];

	/* Verbosity level */
	lkverbosity verbose;

	__attribute__ ((format (printf, 4, 5)))
	void (*log_message)(const char *file, int line, const char *fn, const char *format, ...);

	__attribute__ ((format (printf, 4, 5)))
	void (*log_error)(const char *file, int line, const char *fn, const char *format, ...);
};

#endif /* LK_DATA_H */