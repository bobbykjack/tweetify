<?php
/*
 * tweetify.inc
 *
 * Ported from Remy Sharp's 'ify' javascript function; see:
 * http://code.google.com/p/twitterjs/source/browse/trunk/src/ify.js
 */


/*
 * Clean a tweet: translate links, usernames beginning '@', and hashtags
 */
function clean_tweet($tweet)
{
	$regexps = array
	(
		"link"  => '/[a-z]+:\/\/[a-z0-9-_]+\.[a-z0-9-_:~%&\?\+#\/.=]+[^:\.,\)\s*$]/i',
		"at"    => '/(^|[^\w]+)\@([a-zA-Z0-9_]{1,15}(\/[a-zA-Z0-9-_]+)*)/',
		"hash"  => "/(^|[^&\w'\"]+)\#([a-zA-Z0-9_]+)/"
	);

	foreach ($regexps as $name => $re)
	{
		$tweet = preg_replace_callback($re, 'parse_tweet_'.$name, $tweet);
	}

	return $tweet;
}

/*
 * Wrap a link element around URLs matched via preg_replace()
 */
function parse_tweet_link($m)
{
	return '<a href="'.$m[0].'">'.(($m[0].length > 25) ? $m[0].substr(0, 24).'...' : $m[0]).'</a>';
}

/*
 * Wrap a link element around usernames matched via preg_replace()
 */
function parse_tweet_at($m)
{
	return $m[1].'@<a href="http://twitter.com/'.$m[2].'">'.$m[2].'</a>';
}

/*
 * Wrap a link element around hashtags matched via preg_replace()
 */
function parse_tweet_hash($m)
{
	return $m[1].'#<a href="http://search.twitter.com/search?q=%23'.$m[2].'">'.$m[2].'</a>';
}
?>